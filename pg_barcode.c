#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "lib/stringinfo.h"
#include <qrencode.h>
#include <dmtx.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(generate_qrcode_svg);
PG_FUNCTION_INFO_V1(generate_datamatrix_svg);

Datum
generate_qrcode_svg(PG_FUNCTION_ARGS)
{
    text *input_text = PG_GETARG_TEXT_P(0);
    char *input_string = text_to_cstring(input_text);

    int input_version = 0;
    if (PG_NARGS() > 1) {
        input_version = PG_GETARG_INT32(1);
        if (input_version < 0) {
            input_version = 0;
        }
    }

    QRcode *qrcode;
    StringInfoData svg;

    qrcode = QRcode_encodeString(input_string, input_version, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (qrcode == NULL)
        ereport(ERROR, (errmsg("Failed to generate QR Code")));

    initStringInfo(&svg);
    appendStringInfoString(&svg, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    appendStringInfo(&svg, "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 %d %d' width='%d' height='%d'>\n",
                     qrcode->width, qrcode->width, qrcode->width, qrcode->width);
    appendStringInfoString(&svg, "<rect x='0' y='0' width='100%' height='100%' fill='white' />\n");

    for (int y = 0; y < qrcode->width; y++) {
        for (int x = 0; x < qrcode->width; x++) {
            if (qrcode->data[y * qrcode->width + x] & 1) {
                appendStringInfo(&svg,
                                "<rect x='%d' y='%d' width='1' height='1' fill='black' />\n",
                                x, y);
            }
        }
    }
    appendStringInfoString(&svg, "</svg>");

    QRcode_free(qrcode);

    PG_RETURN_TEXT_P(cstring_to_text(svg.data));
}

Datum
generate_datamatrix_svg(PG_FUNCTION_ARGS)
{
    text *input_text = PG_GETARG_TEXT_P(0);
    char *input_string = text_to_cstring(input_text);

    int input_symbol = DmtxSymbolSquareAuto;
    if (PG_NARGS() > 1) {
        input_symbol = PG_GETARG_INT32(1);
        if (input_symbol < DmtxSymbolSquareAuto) {
            input_symbol = DmtxSymbolSquareAuto;
        }
    }

    int module_size = 1;
    if (PG_NARGS() > 2) {
        module_size = PG_GETARG_INT32(2);
        if (module_size < 1) {
            module_size = 1;
        }
    }
    StringInfoData svg;
    char buffer[1024];

    DmtxEncode *encoder = dmtxEncodeCreate();
    if (encoder == NULL)
        ereport(ERROR, (errmsg("Failed to create Datamatrix encoder")));

    dmtxEncodeSetProp(encoder, DmtxPropPixelPacking, DmtxPack24bppRGB);
    dmtxEncodeSetProp(encoder, DmtxPropSizeRequest, input_symbol);
    dmtxEncodeSetProp(encoder, DmtxPropMarginSize, 1);

    if (!dmtxEncodeDataMatrix(encoder, strlen(input_string), (unsigned char *)input_string)) {
        dmtxEncodeDestroy(&encoder);
        ereport(ERROR, (errmsg("Failed to encode Datamatrix")));
    }

    int width = dmtxImageGetProp(encoder->image, DmtxPropWidth);
    int height = dmtxImageGetProp(encoder->image, DmtxPropHeight);
    int svg_width = width * module_size;
    int svg_height = height * module_size;

    initStringInfo(&svg);
    appendStringInfoString(&svg, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    appendStringInfoString(&svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ");
    snprintf(buffer, sizeof(buffer), "width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\">\n",
             svg_width, svg_height, svg_width, svg_height);
    appendStringInfoString(&svg, buffer);

    appendStringInfoString(&svg, "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r_value, g_value, b_value;
            int inverted_y = height - 1 - y;

            dmtxImageGetPixelValue(encoder->image, x, y, 0, &r_value);
            dmtxImageGetPixelValue(encoder->image, x, y, 1, &g_value);
            dmtxImageGetPixelValue(encoder->image, x, y, 2, &b_value);

            if (r_value == 0 && g_value == 0 && b_value == 0) {
                snprintf(buffer, sizeof(buffer),
                        "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"black\"/>\n",
                        x * module_size, inverted_y * module_size, module_size, module_size);
                appendStringInfoString(&svg, buffer);
            }
        }
    }

    // Fermeture du SVG
    appendStringInfoString(&svg, "</svg>");

    dmtxEncodeDestroy(&encoder);

    PG_RETURN_TEXT_P(cstring_to_text(svg.data));
}