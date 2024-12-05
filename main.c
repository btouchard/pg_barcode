#include <stdio.h>
#include "qrcode.h"
#include "datamatrix.h"

int main() {
    const char *text = "Bonjour, voici un exemple !";

    // Génération d'un QR code
    generate_qrcode(text, "qrcode.pbm");

    // Génération d'une Data Matrix
    generate_datamatrix(text, "datamatrix.pbm");

    return 0;
}
