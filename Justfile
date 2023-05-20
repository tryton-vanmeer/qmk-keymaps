download-qmk-firmware:
  #!/bin/sh
  if [ -d qmk_firmware ]; then
    cd qmk_firmware
    git pull
    git submodule update --init --recursive
  else
    git clone --recurse-submodules -j8 --depth 1 https://github.com/qmk/qmk_firmware.git
  fi

build: download-qmk-firmware
  podman run --rm -it \
    --userns=keep-id \
    --workdir /qmk_firmware \
    --volume ./qmk_firmware:/qmk_firmware:z \
    --volume ./massdrop-alt:/qmk_firmware/keyboards/massdrop/alt/keymaps/tryton:z \
    docker.io/qmkfm/qmk_cli \
    qmk compile -j12 -kb massdrop/alt -km tryton
  cp qmk_firmware/massdrop_alt_tryton.bin .

flash:
  sudo mdloader --first --download massdrop_alt_tryton.bin --restart

generate-pngs:
  rsvg-convert assets/massdrop-alt/layer0.svg -o assets/massdrop-alt/layer0.png
  rsvg-convert assets/massdrop-alt/layer1.svg -o assets/massdrop-alt/layer1.png
  rsvg-convert assets/massdrop-alt/layer2.svg -o assets/massdrop-alt/layer2.png
