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

#ifndef MINDSPORE_ANF_NODE_PARSER_REGISTRY_H
#define MINDSPORE_ANF_NODE_PARSER_REGISTRY_H
#include "src/common/anf_exporter/anf_populater/anf_node_populater.h"
#include <unordered_map>
#include <string>
namespace mindspore::lite {
class AnfNodePopulaterRegistry {
 public:
  AnfNodePopulaterRegistry() = default;
  virtual ~AnfNodePopulaterRegistry() = default;
  static AnfNodePopulaterRegistry *GetInstance();
  AnfNodePopulater *GetNodePopulater(const std::string &name);
  void SetNodePopulater(const std::string &name, AnfNodePopulater *parser);

 private:
  std::unordered_map<std::string, AnfNodePopulater *> parsers;
};

class AnfNodePopulaterRegistrar {
 public:
  AnfNodePopulaterRegistrar(const std::string &name, AnfNodePopulater *parser) {
    AnfNodePopulaterRegistry::GetInstance()->SetNodePopulater(name, parser);
  }
};
}  // namespace mindspore::lite

#endif  // MINDSPORE_ANF_NODE_PARSER_REGISTRY_H
