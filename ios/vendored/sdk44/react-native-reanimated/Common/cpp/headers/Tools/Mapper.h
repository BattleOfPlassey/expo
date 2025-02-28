#pragma once

#include <ABI44_0_0jsi/ABI44_0_0jsi.h>
#include <stdio.h>
#include <memory>
#include <vector>
#include "NativeReanimatedModule.h"
#include "ShareableValue.h"

using namespace ABI44_0_0facebook;

namespace ABI44_0_0reanimated {

class MapperRegistry;

struct ViewDescriptor {
  int tag;
  jsi::Value name;
};

class Mapper : public std::enable_shared_from_this<Mapper> {
  friend MapperRegistry;

 private:
  unsigned long id;
  NativeReanimatedModule *module;
  std::shared_ptr<jsi::Function> mapper;
  std::vector<std::shared_ptr<MutableValue>> inputs;
  std::vector<std::shared_ptr<MutableValue>> outputs;
  bool dirty = true;
  std::shared_ptr<jsi::Function> userUpdater;
  UpdaterFunction *updateProps;
  int optimalizationLvl = 0;
  std::shared_ptr<ShareableValue> viewDescriptors;

 public:
  Mapper(
      NativeReanimatedModule *module,
      unsigned long id,
      std::shared_ptr<jsi::Function> mapper,
      std::vector<std::shared_ptr<MutableValue>> inputs,
      std::vector<std::shared_ptr<MutableValue>> outputs);
  void execute(jsi::Runtime &rt);
  void enableFastMode(
      const int optimalizationLvl,
      const std::shared_ptr<ShareableValue> &updater,
      const std::shared_ptr<ShareableValue> &jsViewDescriptors);
  virtual ~Mapper();
};

} // namespace reanimated
