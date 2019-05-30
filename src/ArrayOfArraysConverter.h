#include "ArrayConverter.h"

#ifndef __FF_ARRAY_OF_ARRAYS_CONVERTER_H__
#define __FF_ARRAY_OF_ARRAYS_CONVERTER_H__

template <class ElementConverterImpl, class ElementCastType = ElementConverterImpl::Type>
class ArrayOfArraysConverterImpl : private ArrayConverterType<ElementConverterImpl, ElementCastType> {
public:
	typedef std::vector<std::vector<ElementConverterImpl::Type>> Type;

	static const char* getTypeName() {
		return "array";
	}

	static bool unwrap(std::vector<std::vector<ElementCastType>>* vecOfVecs, v8::Local<v8::Value> jsVal) {
		if (!jsVal->IsArray()) {
			return true;
		}

		v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(jsVal);
		for (uint i = 0; i < jsArr->Length(); i++) {
			std::vector<CastType> vec;
			Nan::TryCatch tryCatch;
			if (ArrayConverterType<ElementConverterImpl, ElementCastType>::unwrap(&vec, Nan::Get(jsArr, i).ToLocalChecked())) {
				tryCatch.ReThrow();
				return true;
			}
			vecOfVecs->push_back(vec);
		}
		return false;
	}

	static v8::Local<v8::Value> wrap(std::vector<std::vector<ElementCastType>> vec) {
		v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
		for (uint i = 0; i < jsArr->Length(); i++) {
			Nan::Set(jsArr, i, ArrayConverterType<Converter, T, CastType>::wrap(vec.at(i)));
		}
		return jsArr;
	}
};

#endif
