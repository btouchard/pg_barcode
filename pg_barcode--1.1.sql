CREATE FUNCTION generate_qrcode_svg(input TEXT, integer DEFAULT 0) RETURNS TEXT
AS 'MODULE_PATHNAME', 'generate_qrcode_svg'
    LANGUAGE C;

-- Exemple d'utilisation :
-- SELECT generate_qrcode_svg('Hello, PostgreSQL!');
-- SELECT generate_qrcode_svg('Hello, PostgreSQL!', 2);

CREATE FUNCTION generate_datamatrix_svg(input TEXT, integer DEFAULT 0, integer DEFAULT 0) RETURNS TEXT
AS 'MODULE_PATHNAME', 'generate_datamatrix_svg'
    LANGUAGE C;

-- Exemple d'utilisation :
-- SELECT generate_datamatrix_svg('Hello, PostgreSQL!', -2);
-- SELECT generate_datamatrix_svg('Hello, PostgreSQL!', 2, 5);
