#ifndef __LOG_H__
#define __LOG_H__

#define LOG(x) \
    do { \
        std::cerr << x << std::endl; \
    } while (0);

#endif /* __LOG_H__ */
