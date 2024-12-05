#include <stdio.h>
#include <stdlib.h>
#include <qrencode.h>
#include "qrcode.h"

void generate_qrcode(const char *text, const char *output_file) {
    QRcode *qrcode = QRcode_encodeString(text, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (qrcode == NULL) {
        fprintf(stderr, "Erreur lors de la génération du QR code.\n");
        return;
    }

    FILE *file = fopen(output_file, "wb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier pour écriture.\n");
        QRcode_free(qrcode);
        return;
    }

    // Ecriture en format PGM (Portable Gray Map)
    fprintf(file, "P5\n%d %d\n255\n", qrcode->width, qrcode->width);
    fwrite(qrcode->data, qrcode->width * qrcode->width, 1, file);

    fclose(file);
    QRcode_free(qrcode);
    printf("QR code généré et sauvegardé dans %s.\n", output_file);
}
