FROM supabase/postgres:15.1.1.61

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    pkg-config \
    libdmtx-dev \
    libqrencode-dev

RUN echo "deb http://apt.postgresql.org/pub/repos/apt focal-pgdg main" > /etc/apt/sources.list.d/pgdg.list
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 7FCC7D46ACCC4CF8

RUN apt-get update && apt-get install -y \
    postgresql-server-dev-15 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /pg_barcode

COPY . .

RUN make clean && \
    make && \
    make install

RUN ldconfig
