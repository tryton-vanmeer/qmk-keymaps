FROM registry.fedoraproject.org/fedora-minimal:35

RUN microdnf install --assumeyes \
    avrdude \
    avr-gcc \
    arm-none-eabi-gcc-cs \
    arm-none-eabi-newlib \
    gcc \
    libfl2 \
    && microdnf clean all
