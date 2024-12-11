CREATE FUNCTION generate_qrcode_svg(input TEXT) RETURNS TEXT
AS 'MODULE_PATHNAME', 'generate_qrcode_svg'
    LANGUAGE C;

-- Exemple d'utilisation :
-- SELECT generate_qrcode_svg('Hello, PostgreSQL!');

CREATE FUNCTION generate_datamatrix_svg(input TEXT) RETURNS TEXT
AS 'MODULE_PATHNAME', 'generate_datamatrix_svg'
    LANGUAGE C;

-- Exemple d'utilisation :
-- SELECT generate_datamatrix_svg('Hello, PostgreSQL!');
