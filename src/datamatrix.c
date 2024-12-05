#include <stdio.h>
#include <stdlib.h>
#include <dmtx.h>
#include "datamatrix.h"
#include <string.h>

void generate_datamatrix(const char *text, const char *output_file) {
    DmtxEncode *encoder = dmtxEncodeCreate();
    if (encoder == NULL) {
        fprintf(stderr, "Erreur lors de la création de l'encodeur Data Matrix.\n");
        return;
    }

    int ret = dmtxEncodeDataMatrix(encoder, strlen(text), (unsigned char *)text);
    if (ret == 0) {
        fprintf(stderr, "Erreur lors de l'encodage du texte en Data Matrix.\n");
        dmtxEncodeDestroy(&encoder);
        return;
    }

    FILE *file = fopen(output_file, "wb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier pour écriture.\n");
        dmtxEncodeDestroy(&encoder);
        return;
    }

    // Ecriture en format PBM (Portable Bitmap)
    fprintf(file, "P4\n%d %d\n", encoder->image->width, encoder->image->height);
    fwrite(encoder->image->pxl, encoder->image->bytesPerPixel, encoder->image->height * encoder->image->width, file);

    fclose(file);
    dmtxEncodeDestroy(&encoder);
    printf("Data Matrix générée et sauvegardée dans %s.\n", output_file);
}
