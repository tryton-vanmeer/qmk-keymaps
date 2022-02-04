download-qmk-firmware:
  #!/bin/sh
  if [ -d qmk_firmware ]; then
    cd qmk_firmware
    git pull
  else
    git clone --depth 1 https://github.com/qmk/qmk_firmware.git
  fi

build: download-qmk-firmware
  podman run --rm -it \
    --userns=keep-id \
    --workdir /qmk_firmware \
    --volume ./qmk_firmware:/qmk_firmware \
    docker.io/qmkfm/qmk_cli bash