/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>
#include "mindspore/core/utils/log_adapter.h"
#include "common/common_test.h"
#include "mindspore/lite/src/runtime/kernel/arm/fp32/matmul.h"
#include "mindspore/lite/src/runtime/kernel/arm/opclib/fp32/matmul.h"
#include "src/kernel_registry.h"
#include "src/lite_kernel.h"

namespace mindspore {
class TestMatMulFp32 : public mindspore::Common {
 public:
  TestMatMulFp32() {}
};

TEST_F(TestMatMulFp32, Row2Col8Test1) {
  float in[] = {0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90,
                0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.09, 0.50, 0.39,
                0.09, 0.93, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31,
                0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08,
                0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02,
                0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52};
  float co[] = {0.21, 0.67, 0.53, 0.09, 0.43, 0.35, 0.04, 0.43, 0.38, 0.81, 0.97, 0.50, 0.14, 0.52, 0.10, 0.14,
                0.81, 0.57, 0.92, 0.39, 0.67, 0.02, 0.18, 0.67, 0.98, 0.70, 0.35, 0.09, 0.10, 0.33, 0.92, 0.10,
                0.09, 0.27, 0.74, 0.93, 0.73, 0.99, 0.46, 0.73, 0.68, 0.90, 0.78, 0.91, 0.37, 0.49, 0.08, 0.37,
                0.02, 0.07, 0.87, 0.20, 0.24, 0.67, 0.04, 0.24, 0.33, 0.13, 0.23, 0.97, 0.93, 0.75, 0.24, 0.93,
                0.85, 0.03, 0.34, 0.61, 0.31, 0.66, 0.52, 0.31, 0.35, 0.04, 0,    0,    0,    0,    0,    0,
                0.52, 0.10, 0,    0,    0,    0,    0,    0,    0.02, 0.18, 0,    0,    0,    0,    0,    0,
                0.33, 0.92, 0,    0,    0,    0,    0,    0,    0.99, 0.46, 0,    0,    0,    0,    0,    0,
                0.49, 0.08, 0,    0,    0,    0,    0,    0,    0.67, 0.04, 0,    0,    0,    0,    0,    0,
                0.75, 0.24, 0,    0,    0,    0,    0,    0,    0.66, 0.52, 0,    0,    0,    0,    0,    0};
  float out[144] = {0};
  RowMajor2Col8Major(in, out, 10, 9);
  CompareOutputData(out, co, 144, 0.0001);
}

TEST_F(TestMatMulFp32, Row2Col8Test2) {
  float in[] = {0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90,
                0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.09, 0.50, 0.39,
                0.09, 0.93, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31,
                0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08,
                0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02,
                0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52};
  float co[] = {0.21, 0.68, 0.81, 0.07, 0.92, 0.23, 0.09, 0.61, 0.38, 0.02, 0.57, 0.13, 0.35, 0.34, 0.93,
                0.43, 0.81, 0.33, 0.70, 0.03, 0.74, 0.09, 0.91, 0.14, 0.98, 0.85, 0.27, 0.53, 0.78, 0.50,
                0.20, 0.67, 0.09, 0.67, 0.90, 0.97, 0.87, 0.39, 0.97, 0.10, 0.73, 0.35, 0.49, 0.10, 0.04,
                0.67, 0.93, 0.33, 0.37, 0.52, 0.67, 0.18, 0.24, 0.10, 0.31, 0.99, 0.24, 0.02, 0.75, 0.92,
                0.52, 0.73, 0.35, 0.49, 0.93, 0.33, 0.66, 0.46, 0.43, 0.37, 0.52, 0.67, 0.31, 0.99, 0.04,
                0.08, 0.14, 0.24, 0.02, 0.75, 0.66, 0.46, 0,    0,    0,    0,    0,    0,    0.04, 0.08,
                0,    0,    0,    0,    0,    0,    0.10, 0.04, 0,    0,    0,    0,    0,    0,    0.18,
                0.24, 0,    0,    0,    0,    0,    0,    0.92, 0.52, 0,    0,    0,    0,    0,    0};
  float out[120] = {0};
  RowMajor2Col8Major(in, out, 18, 5);
  CompareOutputData(out, co, 120, 0.0001);
}

TEST_F(TestMatMulFp32, Row8x82RowTest1) {
  float in[] = {0.21, 0.38, 0.81, 0.98, 0.09, 0, 0, 0, 0.68, 0.02, 0.33, 0.85, 0.67, 0, 0, 0,
                0.81, 0.57, 0.70, 0.27, 0.90, 0, 0, 0, 0.07, 0.13, 0.03, 0.53, 0.97, 0, 0, 0,
                0.92, 0.35, 0.74, 0.78, 0.87, 0, 0, 0, 0.23, 0.34, 0.09, 0.50, 0.39, 0, 0, 0,
                0.09, 0.93, 0.91, 0.20, 0.97, 0, 0, 0, 0.61, 0.43, 0.14, 0.67, 0.10, 0, 0, 0,
                0.73, 0.37, 0.24, 0.93, 0.31, 0, 0, 0, 0.35, 0.52, 0.02, 0.33, 0.99, 0, 0, 0,
                0.49, 0.67, 0.75, 0.66, 0.04, 0, 0, 0, 0.10, 0.18, 0.92, 0.46, 0.08, 0, 0, 0,
                0.04, 0.24, 0.52, 0.43, 0.14, 0, 0, 0, 0.67, 0.10, 0.73, 0.37, 0.24, 0, 0, 0,
                0.93, 0.31, 0.35, 0.52, 0.02, 0, 0, 0, 0.33, 0.99, 0.49, 0.67, 0.75, 0, 0, 0,
                0.66, 0.04, 0.10, 0.18, 0.92, 0, 0, 0, 0.46, 0.08, 0.04, 0.24, 0.52, 0, 0, 0,
                0,    0,    0,    0,    0,    0, 0, 0, 0,    0,    0,    0,    0,    0, 0, 0,
                0,    0,    0,    0,    0,    0, 0, 0, 0,    0,    0,    0,    0,    0, 0, 0,
                0,    0,    0,    0,    0,    0, 0, 0, 0,    0,    0,    0,    0,    0, 0, 0};
  float co[] = {0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90,
                0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.09, 0.50, 0.39,
                0.09, 0.93, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31,
                0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08,
                0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02,
                0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52};
  float out[90] = {0};
  Row8x8Major2RowMajor(in, out, 18, 5);
  CompareOutputData(out, co, 90, 0.0001);
}

TEST_F(TestMatMulFp32, Row8x82RowTest2) {
  float in[] = {0.21, 0.38, 0.81, 0.98, 0.09, 0, 0, 0, 0.68, 0.02, 0.33, 0.85, 0.67, 0, 0, 0,
                0.81, 0.57, 0.70, 0.27, 0.90, 0, 0, 0, 0.07, 0.13, 0.03, 0.53, 0.97, 0, 0, 0,
                0.92, 0.35, 0.74, 0.78, 0.87, 0, 0, 0, 0.23, 0.34, 0.09, 0.50, 0.39, 0, 0, 0,
                0,    0,    0,    0,    0,    0, 0, 0, 0,    0,    0,    0,    0,    0, 0, 0};
  float co[] = {0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90,
                0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.09, 0.50, 0.39};
  float out[30] = {0};
  Row8x8Major2RowMajor(in, out, 6, 5);
  CompareOutputData(out, co, 30, 0.0001);
}

TEST_F(TestMatMulFp32, Row8x82RowTest3) {
  float in[] = {
    0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.67, 0.10, 0.73,
    0.37, 0.24, 0.93, 0.31, 0.35, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52, 0.43, 0.14, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04,
    0.10, 0.18, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.87, 0.23, 0.34, 0.09, 0.50, 0.39, 0.09, 0.93, 0.93,
    0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.75, 0.66, 0.04, 0.10,
    0.18, 0.92, 0.46, 0.08, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02,
    0.33, 0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.92, 0.46,
    0.08, 0.04, 0.24, 0.52, 0.43, 0.14, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.87, 0.23, 0.34, 0.09, 0.50,
    0.39, 0.09, 0.93, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24,
    0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.21, 0.38, 0.81,
    0.98, 0.09, 0.68, 0.02, 0.33, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90, 0.07, 0.09, 0.50, 0.39, 0.09, 0.93, 0.91, 0.20, 0.97, 0.52,
    0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.92, 0.46, 0.08, 0.04,
    0.24, 0.52, 0.21, 0.38, 0.27, 0.90, 0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14, 0.67,
    0.10, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.04, 0.24,
    0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.85, 0.67, 0.81, 0.57, 0.70,
    0.27, 0.90, 0.07, 0.09, 0.50, 0.39, 0.09, 0.93, 0.91, 0.20, 0.97, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66,
    0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.27, 0.90, 0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.91, 0.20, 0.97,
    0.61, 0.43, 0.14, 0.67, 0.10, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33,
    0.99, 0.49, 0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.85,
    0.67, 0.81, 0.57, 0.70, 0.27, 0.90, 0.07, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0.13, 0.03, 0.53, 0,    0,    0,    0,    0,    0.61, 0.43, 0.14, 0,    0,    0,    0,
    0,    0.04, 0.10, 0.18, 0,    0,    0,    0,    0,    0.52, 0.02, 0.33, 0,    0,    0,    0,    0,    0.81, 0.98,
    0.09, 0,    0,    0,    0,    0,    0.35, 0.74, 0.78, 0,    0,    0,    0,    0,    0.73, 0.37, 0.24, 0,    0,
    0,    0,    0,    0.08, 0.04, 0.24, 0,    0,    0,    0,    0,    0.67, 0.75, 0.67, 0,    0,    0,    0,    0,
    0.37, 0.24, 0.93, 0,    0,    0,    0,    0,    0.04, 0.24, 0.52, 0,    0,    0,    0,    0,    0.13, 0.03, 0.53,
    0,    0,    0,    0,    0,    0.61, 0.43, 0.14, 0,    0,    0,    0,    0,    0.04, 0.10, 0.18, 0,    0,    0,
    0,    0,    0.52, 0.02, 0.33, 0,    0,    0,    0,    0,    0.35, 0.74, 0.78, 0,    0,    0,    0,    0,    0.73,
    0.37, 0.24, 0,    0,    0,    0,    0,    0.08, 0.04, 0.24, 0,    0,    0,    0,    0,    0.67, 0.75, 0.67, 0,
    0,    0,    0,    0,    0.37, 0.24, 0.93, 0,    0,    0,    0,    0,    0.04, 0.24, 0.52, 0,    0,    0,    0,
    0,    0.13, 0.03, 0.53, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0};
  float co[] = {
    0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90, 0.07, 0.13, 0.03, 0.53,
    0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.09, 0.50, 0.39, 0.09, 0.93, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14,
    0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18,
    0.92, 0.46, 0.08, 0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33,
    0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52, 0.21, 0.38, 0.81, 0.98, 0.09,
    0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90, 0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.35, 0.74, 0.78,
    0.87, 0.23, 0.34, 0.09, 0.50, 0.39, 0.09, 0.93, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24,
    0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24,
    0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.67,
    0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93,
    0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52,
    0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90, 0.07, 0.13, 0.03, 0.53,
    0.97, 0.92, 0.35, 0.74, 0.78, 0.87, 0.23, 0.34, 0.09, 0.50, 0.39, 0.09, 0.93, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14,
    0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18,
    0.92, 0.46, 0.08, 0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33,
    0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90, 0.07, 0.13, 0.03, 0.53, 0.97, 0.92, 0.35, 0.74, 0.78,
    0.87, 0.23, 0.34, 0.09, 0.50, 0.39, 0.09, 0.93, 0.91, 0.20, 0.97, 0.61, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24,
    0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24,
    0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93, 0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.67,
    0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52, 0.43, 0.14, 0.67, 0.10, 0.73, 0.37, 0.24, 0.93,
    0.31, 0.35, 0.52, 0.02, 0.33, 0.99, 0.49, 0.67, 0.75, 0.66, 0.04, 0.10, 0.18, 0.92, 0.46, 0.08, 0.04, 0.24, 0.52,
    0.21, 0.38, 0.81, 0.98, 0.09, 0.68, 0.02, 0.33, 0.85, 0.67, 0.81, 0.57, 0.70, 0.27, 0.90, 0.07, 0.13, 0.03, 0.53};
  float out[418] = {0};
  Row8x8Major2RowMajor(in, out, 22, 19);
  CompareOutputData(out, co, 418, 0.0001);
}

int MMTestInit(std::vector<lite::tensor::Tensor *> *inputs_, std::vector<lite::tensor::Tensor *> *outputs_,
               float *a_ptr, float *b_ptr, std::vector<int> a_shape, std::vector<int> b_shape,
               std::vector<int> c_shape) {
  auto in_t =
    new lite::tensor::Tensor(kNumberTypeFloat, a_shape, schema::Format_NHWC, static_cast<schema::NodeType>(1));
  in_t->MallocData();
  memcpy(in_t->Data(), a_ptr, sizeof(float) * in_t->ElementsNum());
  inputs_->push_back(in_t);

  auto weight_t =
    new lite::tensor::Tensor(kNumberTypeFloat, b_shape, schema::Format_NHWC, static_cast<schema::NodeType>(1));
  weight_t->MallocData();
  memcpy(weight_t->Data(), b_ptr, sizeof(float) * weight_t->ElementsNum());
  inputs_->push_back(weight_t);

  auto out_t =
    new lite::tensor::Tensor(kNumberTypeFloat, c_shape, schema::Format_NHWC, static_cast<schema::NodeType>(1));
  out_t->MallocData();
  outputs_->push_back(out_t);

  return out_t->ElementsNum();
}

TEST_F(TestMatMulFp32, simple) {
  std::vector<lite::tensor::Tensor *> inputs_;
  std::vector<lite::tensor::Tensor *> outputs_;
  auto matmul_param = new MatMulParameter();
  matmul_param->a_transpose_ = false;
  matmul_param->b_transpose_ = false;
  matmul_param->has_bias_ = false;
  float a[] = {-3.2366564, -4.7733846, -7.8329225, 16.146885, 5.060793,  -6.1471,  -1.7680453, -6.5721383,
               17.87506,   -5.1192183, 10.742863,  1.4536934, 19.693445, 19.45783, 5.063163,   0.5234792};
  float b[] = {-0.0024438887, 0.0006738146, -0.008169129, 0.0021510671,  -0.012470592,   -0.0053063435,
               0.006050155,   0.008656233,  0.012911413,  -0.0028635843, -0.00034080597, -0.0010622552,
               -0.012254699,  -0.01312836,  0.0025241964, -0.004706142,  0.002451482,    -0.009558459,
               0.004481974,   0.0033251503, -0.011705584, -0.001720293,  -0.0039410214,  -0.0073637343};
  std::vector<int> a_shape = {1, 2, 8};
  std::vector<int> b_shape = {1, 8, 3};
  std::vector<int> c_shape = {1, 2, 3};
  int total_size = MMTestInit(&inputs_, &outputs_, a, b, a_shape, b_shape, c_shape);
  auto ctx = new lite::Context;
  ctx->thread_num_ = 2;
  auto mm = new kernel::MatmulCPUKernel(reinterpret_cast<OpParameter *>(matmul_param), inputs_, outputs_, ctx);
  mm->Init();
  mm->Run();
  float correct[] = {-0.1256939023733139, -0.07744802534580231,  0.07410638779401779,
                     -0.3049793541431427, -0.027687929570674896, -0.18109679222106934};
  CompareOutputData(reinterpret_cast<float *>(outputs_[0]->Data()), correct, total_size, 0.0001);
  delete matmul_param;
  delete mm;
  for (auto t : inputs_) delete t;
  for (auto t : outputs_) delete t;
}

TEST_F(TestMatMulFp32, simple_transb) {
  std::vector<lite::tensor::Tensor *> inputs_;
  std::vector<lite::tensor::Tensor *> outputs_;
  auto matmul_param = new MatMulParameter();
  matmul_param->a_transpose_ = false;
  matmul_param->b_transpose_ = true;
  matmul_param->has_bias_ = false;
  float a[] = {-3.2366564, -4.7733846, -7.8329225, 16.146885, 5.060793,  -6.1471,  -1.7680453, -6.5721383,
               17.87506,   -5.1192183, 10.742863,  1.4536934, 19.693445, 19.45783, 5.063163,   0.5234792};
  float b[] = {-0.0024438887, 0.0006738146, -0.008169129, 0.0021510671,  -0.012470592,   -0.0053063435,
               0.006050155,   0.008656233,  0.012911413,  -0.0028635843, -0.00034080597, -0.0010622552,
               -0.012254699,  -0.01312836,  0.0025241964, -0.004706142,  0.002451482,    -0.009558459,
               0.004481974,   0.0033251503, -0.011705584, -0.001720293,  -0.0039410214,  -0.0073637343};
  std::vector<int> a_shape = {1, 2, 8};
  std::vector<int> b_shape = {1, 3, 8};
  std::vector<int> c_shape = {1, 2, 3};
  int total_size = MMTestInit(&inputs_, &outputs_, a, b, a_shape, b_shape, c_shape);
  auto ctx = new lite::Context;
  ctx->thread_num_ = 2;
  auto mm = new kernel::MatmulCPUKernel(reinterpret_cast<OpParameter *>(matmul_param), inputs_, outputs_, ctx);
  mm->Init();
  mm->Run();
  float correct[] = {0.00533547, 0.002545945, 0.062974121, -0.445441471, -0.246223617, -0.142070031};
  CompareOutputData(reinterpret_cast<float *>(outputs_[0]->Data()), correct, total_size, 0.0001);
  delete matmul_param;
  delete mm;
  for (auto t : inputs_) delete t;
  for (auto t : outputs_) delete t;
}

TEST_F(TestMatMulFp32, batch) {
  std::vector<lite::tensor::Tensor *> inputs_;
  std::vector<lite::tensor::Tensor *> outputs_;
  auto matmul_param = new MatMulParameter();
  matmul_param->a_transpose_ = false;
  matmul_param->b_transpose_ = true;
  matmul_param->has_bias_ = false;
  float a[] = {-4.946672525326248,  11.154420027909701,  -7.831129637356922,  17.309845099949953,  -10.46177877610444,
               2.5412751480833897,  2.700113860276929,   -12.616715572097341, -15.513316568881574, -9.513294738065516,
               17.931148376418896,  -10.83801964632579,  -14.023733862948017, -14.50805001403956,  0.7952221556310306,
               6.619720423569035,   -19.277904230909357, -13.450479287024839, 19.914652156692625,  16.542571697048878,
               -2.9715041389268926, 4.949555349889412,   -1.9408110276290103, -15.062828261031868, 0.20012569643335,
               8.260383531209776,   3.1092344458607357,  16.742272486091487,  17.31277252415167,   -16.60303202099434,
               -8.980314693173042,  -11.735087989358268, -14.918976184088514, -11.347592686892733, 11.808756029220604,
               -18.76179414554809,  7.579758962360987,   3.13240880962163,    6.528181981442103,   -16.802624652419794,
               -14.323146919914901, -16.197579076296144, 9.738053920125779,   -12.245780062949866, 8.817905278096319,
               0.5261391331275007,  -18.26152522535471,  -2.400461208771226};
  float b[] = {
    -0.895183867395529,    -0.8146900207660068,   -0.27931593219652817,  0.783554361201179,     -0.05080215007779798,
    -0.9879631271568501,   0.07710949009001333,   -0.9562579726211344,   0.29505553318356825,   -0.26651960351085124,
    -0.12755456259718279,  -0.8221417897250098,   -0.5094334041431876,   -0.9117373380256013,   0.991501784215064,
    0.20131976450979394,   0.07889260559412059,   -0.8138407752750305,   -0.047622075866657454, -0.2778043115153188,
    -0.6269973420163957,   -0.44345812666611617,  -0.8571568605933642,   0.020192166011526735,  0.4860054298402434,
    0.41525925469513614,   -0.40270506445219967,  -0.8716538067535347,   0.5276448387223114,    0.6064500154192936,
    -0.9553204135772526,   0.3253219646257437,    -0.7237956595774822,   0.3271284879679077,    -0.534543967339336,
    -0.4076498484281894,   0.01574797075171963,   -0.37322004720586244,  0.16425071396119928,   -0.5328652244800547,
    0.7389336170615435,    -0.6552069958923377,   -0.042305872596973604, -0.6714941466767734,   -0.9281411415119043,
    -0.7748558258281224,   -0.6209799945964443,   0.02526428593887675,   -0.44984776800225856,  0.6281401952319337,
    0.9907258228680276,    0.6288646615999687,    -0.82076880150175,     0.3065944740797497,    -0.29201038744043584,
    -0.025685501802048982, -0.07273175145419652,  0.9370449239208709,    -0.8233807408078093,   -0.4195634619023012,
    0.9799555630257346,    -0.23461882935715228,  -0.8884793313829993,   -0.4760267734754635,   -0.2874539543614072,
    -0.8795685985480997,   -0.08099698251915255,  -0.1626521023321741,   -0.9337167240793414,   0.40924842916829207,
    -0.7375713045221615,   -0.0065659291539015285};
  std::vector<int> a_shape = {3, 2, 8};
  std::vector<int> b_shape = {3, 3, 8};
  std::vector<int> c_shape = {3, 2, 3};
  int total_size = MMTestInit(&inputs_, &outputs_, a, b, a_shape, b_shape, c_shape);
  auto ctx = new lite::Context;
  ctx->thread_num_ = 1;
  auto mm = new kernel::MatmulCPUKernel(reinterpret_cast<OpParameter *>(matmul_param), inputs_, outputs_, ctx);
  mm->Init();
  mm->Run();
  float correct[] = {21.38518524169922,  -14.514888763427734, -11.040614128112793, 16.91403579711914,
                     27.07421112060547,  23.35394287109375,   -39.006141662597656, -2.021998405456543,
                     -17.63555145263672, -8.490625381469727,  5.317771911621094,   -14.561882019042969,
                     -7.251564025878906, -2.508212089538574,  5.86458683013916,    -3.466249465942383,
                     8.869029998779297,  25.034008026123047};

  float *output = reinterpret_cast<float *>(outputs_[0]->Data());
  for (int i = 0; i < 18; ++i) printf("%f ", output[i]);
  CompareOutputData(reinterpret_cast<float *>(outputs_[0]->Data()), correct, total_size, 0.0001);
  delete matmul_param;
  delete mm;
  for (auto t : inputs_) delete t;
  for (auto t : outputs_) delete t;
}
}  // namespace mindspore
