// Copyright 2014 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Functions to convert brotli-related data structures into the
// brotli bit stream. The functions here operate under
// assumption that there is enough space in the storage, i.e., there are
// no out-of-range checks anywhere.
//
// These functions do bit addressing into a byte array. The byte array
// is called "storage" and the index to the bit is called storage_ix
// in function arguments.

#ifndef BROTLI_ENC_BROTLI_BIT_STREAM_H_
#define BROTLI_ENC_BROTLI_BIT_STREAM_H_

#include <stddef.h>
#include <stdint.h>

namespace brotli {

// All Store functions here will use a storage_ix, which is always the bit
// position for the current storage.

// Stores a number between 0 and 255.
void StoreVarLenUint8(int n, int* storage_ix, uint8_t* storage);

// Stores the compressed meta-block header.
void StoreCompressedMetaBlockHeader(bool final_block,
                                    int length,
                                    int* storage_ix,
                                    uint8_t* storage);

// Stores the uncompressed meta-block header.
void StoreUncompressedMetaBlockHeader(int length,
                                      int* storage_ix,
                                      uint8_t* storage);

// Stores a context map where the histogram type is always the block type.
void StoreTrivialContextMap(int num_types,
                            int context_bits,
                            int* storage_ix,
                            uint8_t* storage);

// Builds a Huffman tree from histogram[0:length] into depth[0:length] and
// bits[0:length] and stores the encoded tree to the bit stream.
void BuildAndStoreHuffmanTree(const int *histogram,
                              const int length,
                              const int quality,
                              uint8_t* depth,
                              uint16_t* bits,
                              int* storage_ix,
                              uint8_t* storage);

}  // namespace brotli

#endif  // BROTLI_ENC_BROTLI_BIT_STREAM_H_