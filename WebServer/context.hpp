#ifndef RECURSE_CONTEXT_HPP
#define RECURSE_CONTEXT_HPP

#include <QtGlobal>
#include <QVariant>
#include <QHash>

#include "request.hpp"
#include "response.hpp"

class Context
{

public:
    Request request;
    Response response;

    //!
    //! \brief set
    //! Set data into context that can be passed around
    //!
    //! \param QString key of the data
    //! \param QString value of the data
    //! \return Context chainable
    //!
    Context &set(const QString &key, const QVariant &value)
    {
        m_data[key] = value;
        return *this;
    }

    //!
    //! \brief get
    //! Get data from context
    //!
    //! \param QString key of the data
    //! \return QString value of the data
    //!
    QVariant get(const QString &key) const
    {
        return m_data[key];
    }

    //!
    //! \brief data
    //! expose key/value data of *void pointer to allow any type of data
    //!
    QHash<QString, void *> data;

private:
    //!
    //! \brief m_data
    //! Context data holder
    //!
    QHash<QString, QVariant> m_data;
};

#endif
