# https://github.com/qmk/qmk_base_container/blob/master/Dockerfile

FROM registry.fedoraproject.org/fedora-minimal:35

RUN microdnf install --assumeyes \
    avrdude \
    avr-gcc \
    arm-none-eabi-gcc-cs \
    arm-none-eabi-newlib \
    gcc \
    libfl2 \
    python \
    pip \
    python3-nose2 \
    python3-yapf \
    && microdnf clean all

RUN python3 -m pip install qmk

ENV QMK_HOME /qmk_firmware