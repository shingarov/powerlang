/*
 * Copyright (c) 2019 Javier Pimas, Jan Vrany

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _CLASSES_H_
#define _CLASSES_H_

#include <cstdint>
#include <Object.h>

typedef S9::VMObject VMObject;
#define DEFINE_CLASS(CLASSNAME, SUPERNAME, SLOTS)                               \
    namespace pst {                                                             \
    struct CLASSNAME : public SUPERNAME                                         \
    {                                                                           \
        SLOTS                                                                   \
    };                                                                          \
    }
#define DEFINE_SLOT(SLOTNAME) Object* s_##SLOTNAME;
#define NIL VMObject

#include "Classes.def"
#undef DEFINE_CLASS
#undef DEFINE_SLOT
#undef NIL

namespace S9 {

class VMMethodDictionary : public pst::MethodDictionary
{
  public:
    OOP<VMObject> lookup(OOP<VMObject> sel);
};

class VMBehavior : public pst::Behavior
{
  public:
    OOP<VMObject> lookup(OOP<VMObject> sel);
};

using VMNativeCode = VMObject* (*)();

class VMMethod : public pst::CompiledMethod
{
  public:
    VMNativeCode getNativeCode()
    {
        uintptr_t code = (uintptr_t)this->s_nativeCode;
        S9_ASSERT((code & 1) && "Native code is not a SmallInteger");
        return (VMNativeCode)(code & ~1);
    }
};

} // namespace S9

#endif /* CLASSES_H_ */