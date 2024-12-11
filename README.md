# pg_barcode

pg_barcode is a PostgreSQL extension that allows you to generate QRCode & Datamatrix in SVG format directly from your database.

## Features

- Generate QRCode or Datamatrix in SVG format
- Simple integration with PostgreSQL
- Based on qrencode & dmtx c libraries

## Prerequisites

- PostgreSQL 9.5 or higher
- PostgreSQL development tools (postgresql-server-dev-all on Debian/Ubuntu systems)
- C compiler (gcc or clang)
- Make

## Installation

1. Clone this repository:
   ```
   git clone https://github.com/btouchard/pg_barcode.git
   cd pg_barcode
   ```

2. Compile the extension:
   ```
   make
   ```

3. Install the extension:
   ```
   sudo make install
   ```

4. Connect to your PostgreSQL database:
   ```
   psql -d your_database
   ```

5. Create the extension:
   ```sql
   CREATE EXTENSION pg_barcode;
   ```

## Usage

Once the extension is installed, you can generate QR codes using the `generate_qrcode_svg` function:

```sql
-- Generate a QR code
SELECT generate_qr_code_svg('https://www.kolapsis.com');
```

Generate Datamatrix using the `generate_datamatrix_svg` function:

```sql
-- Generate a Datamatrix
SELECT generate_datamatrix_svg('https://www.kolapsis.com');
```

## Troubleshooting

If you encounter issues during installation or use of the extension, ensure that:

1. PostgreSQL is properly installed and configured.
2. PostgreSQL development tools are installed.
3. You have the necessary permissions to install the extension.

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE.md](LICENSE) file for details.

## Acknowledgements

- QR Code generator library: https://fukuchi.org/works/qrencode/manual/index.html
- Datamatrix generator: https://github.com/dmtx/libdmtx
- The PostgreSQL community for their excellent resources on extension development.