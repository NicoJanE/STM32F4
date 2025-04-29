FROM debian:stable

# Install dependencies
# xdg-utilsis for live server in VSC (ritwickdey.LiveServer) It is a bit overhead yes
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    make \
    gcc-arm-none-eabi \
    gdb-multiarch \
    openocd \
    stlink-tools \
    libusb-1.0-0-dev \
    usbutils \
    git wget curl unzip git \
    gdb-multiarch gcc-arm-none-eabi \
    binutils-multiarch file telnet \
    xdg-utils \
    graphviz \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# NewLib(C Library for embedded systems)
# Is already installed this is (currently not needed)
# Web page: https://sourceware.org/newlib/
# RUN apt update && apt install -y  libnewlib-arm-none-eabi


# Set up a working directory
WORKDIR /workspace

# Download, unzip, rename, and clean up
#RUN git clone --depth=1 https://github.com/STMicroelectronics/cmsis-device-f4.git CMSIS
RUN git clone --depth=1 https://github.com/STMicroelectronics/cmsis-device-f4.git CMSIS && \
    ls -la /workspace/CMSIS
 
# make link to (classic) binutils-multiarch names
RUN ln -s /usr/bin/nm /usr/bin/nm-multiarch
RUN ln -s /usr/bin/objdump /usr/bin/objdump-multiarch
                        
# Entrypoint shell
CMD ["/bin/bash"]



