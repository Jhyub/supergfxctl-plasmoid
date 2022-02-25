#!/usr/bin/env bash

# Modified based off on https://github.com/Zren 's script.

cd "${TRANSLATION_PATH}" || exit
catalogs=$(find . -name '*.po' | sort)
for cat in $catalogs; do
  catLocale=$(basename "${cat%.*}")
  installPath="./install/share/locale/${catLocale}/LC_MESSAGES/plasma_applet_dev.jhyub.supergfxctl.mo"
  mkdir -p "$(dirname "${installPath}")"
  msgfmt -o "${installPath}" "${cat}"
  echo "Built locale ${cat} to ${installPath}"
done
