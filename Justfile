download-qmk-firmware:
  #!/bin/sh
  if [ -d qmk_firmware ]; then
    pushd qmk_firmware
    git pull
    git submodule update --init --recursive
    popd
  else
    git clone --recurse-submodules -j8 --depth 1 https://github.com/qmk/qmk_firmware.git
  fi
  ln -Trfs ./massdrop-alt qmk_firmware/keyboards/massdrop/alt/keymaps/custom
  ln -Trfs ./keychron-q11 qmk_firmware/keyboards/keychron/q11/ansi_encoder/keymaps/custom

build-massdrop-alt: download-qmk-firmware
  podman run --rm -it \
    --userns=keep-id \
    --workdir /qmk_firmware \
    --volume ./qmk_firmware:/qmk_firmware:z \
    --volume ./massdrop-alt:/qmk_firmware/keyboards/massdrop/alt/keymaps/tryton:z \
    ghcr.io/qmk/qmk_cli \
    qmk compile -j12 -kb massdrop/alt -km tryton
  cp qmk_firmware/massdrop_alt_tryton.bin .

flash-massdrop-alt:
  sudo mdloader --first --download massdrop_alt_tryton.bin --restart

build-keychron-q11: download-qmk-firmware
  podman run --rm -it \
    --userns=keep-id \
    --workdir /qmk_firmware \
    --volume ./qmk_firmware:/qmk_firmware:z \
    --volume ./keychron-q11:/qmk_firmware/keyboards/keychron/q11/ansi_encoder/keymaps/tryton:z \
    ghcr.io/qmk/qmk_cli \
    qmk compile -j12 -kb keychron/q11/ansi_encoder -km tryton
  cp qmk_firmware/keychron_q11_ansi_encoder_tryton.bin .

flash-keychron-q11:
  sudo podman run --rm -it \
    --privileged \
    --volume /dev:/dev \
    --workdir /qmk_firmware \
    --volume ./qmk_firmware:/qmk_firmware:z \
    --volume ./keychron-q11:/qmk_firmware/keyboards/keychron/q11/ansi_encoder/keymaps/tryton:z \
    ghcr.io/qmk/qmk_cli \
    make keychron/q11/ansi_encoder:tryton:flash
