qmk-firmware:
  git submodule update --init --recursive --progress

build:
  podman run --rm -it \
    --userns=keep-id \
    --workdir /qmk_firmware \
    --volume ./qmk_firmware:/qmk_firmware:z \
    --volume ./massdrop-alt:/qmk_firmware/keyboards/massdrop/alt/keymaps/tryton:z \
    docker.io/qmkfm/qmk_cli \
    make -j12 massdrop/alt:tryton
  cp qmk_firmware/massdrop_alt_tryton.bin .

flash:
  sudo mdloader --first --download massdrop_alt_tryton.bin --restart