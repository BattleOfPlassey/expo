package abi44_0_0.expo.modules.kotlin.types

import abi44_0_0.com.facebook.react.bridge.Dynamic
import kotlin.reflect.KType

fun KType.toAnyType(): AnyType = AnyType(this)

class AnyType(val kType: KType) {
  private val converter: TypeConverter<*> by lazy {
    TypeConverterProviderImpl.obtainTypeConverter(kType)
  }

  fun convert(value: Dynamic): Any? = converter.convert(value)
}
