# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

export EXTRA_LIBS="${NACL_CLI_MAIN_LIB} -lppapi_simple \
  -lnacl_io -lppapi -lppapi_cpp -l${NACL_CPP_LIB}"
EXTRA_CONFIGURE_ARGS="\
  --enable-targets=x86_64-nacl,arm-nacl,avr \
  --disable-werror \
  --enable-deterministic-archives \
  --without-zlib"

BuildStep() {
  export CONFIG_SITE
  DefaultBuildStep
}

InstallStep() {
  MakeDir ${PUBLISH_DIR}
  for nexe in binutils/*.nexe gas/*.nexe ld/*.nexe; do
    local name=$(basename $nexe .nexe | sed 's/-new//')
    cp ${nexe} ${PUBLISH_DIR}/${name}_${NACL_ARCH}${NACL_EXEEXT}

    pushd ${PUBLISH_DIR}
    LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
        ${PUBLISH_DIR}/${name}_*${NACL_EXEEXT} \
        -s . \
        -o ${name}.nmf
    popd
  done
}
