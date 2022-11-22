#include <stdint.h>
#include <stddef.h>

#include "vm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  static bool isInitialized = initVM();
  if (isInitialized) interpret((const char *)Data, Size);
  return 0;
}
