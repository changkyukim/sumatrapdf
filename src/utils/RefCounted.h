/* Copyright 2014 the SumatraPDF project authors (see AUTHORS file).
   License: Simplified BSD (see COPYING.BSD) */

#ifndef RefCounted_h
#define RefCounted_h
 
// Auto-generated copy constructors can be incorrect.
// To ensure a given class won't get copy constructor
// or assignment operator silently generated by the
// compiler, derive it from NonCopyable
class NonCopyable {
public:
    NonCopyable() { }

private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

// Note: I don't like ref counting. I've seen to many code bases
// that overused it. Sometimes, however, it's the best solution
// for managing the lifetime of shared objects.
// This is a thread-safe base class for objects that are
// managed by ref counting.
// Newly created objects start with ref count of 1.
// Ref()/UnRef() increase/decrease the ref count.
// When ref count drops to 0, the object is deleted
class RefCounted : NonCopyable {
private:
    LONG refCnt;

protected:
    virtual ~RefCounted() {
        CrashIf(0 != refCnt);
    }

public:
    RefCounted() : refCnt(1) { }

    void AddRef() {
        CrashIf(refCnt <= 0);
        InterlockedIncrement(&refCnt);
    }
    void Release() {
        if (0 == InterlockedDecrement(&refCnt)) {
            delete this;
        }
    }
};

#endif
