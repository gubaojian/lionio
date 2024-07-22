#pragma once

#define DISABLE_COPY_ADN_ASSIGN(ClassName) \
    ClassName(const ClassName &);          \
    void operator=(const ClassName &)