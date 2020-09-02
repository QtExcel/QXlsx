
#ifndef QXLSX_EXPORT_H
#define QXLSX_EXPORT_H

#if defined(BUILD_SHARED_LIBS)
    #if defined(QXlsx_EXPORTS)
        #define QXLSX_EXPORT Q_DECL_EXPORT
    #else
        #define QXLSX_EXPORT Q_DECL_IMPORT
    #endif
#else
    #define QXLSX_EXPORT
#endif

#endif /* QXLSX_EXPORT_H */
