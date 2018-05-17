#include "Packet.h"

// Non-virtual customizable method.
const QByteArray Packet::dump() const
{
    const QByteArray data = specificDump();
    const qint32 packid = specificGetID();
    const qint32 length = data.length();

    QByteArray toDump;
    toDump.append((char*)&packid, sizeof(qint32));
    toDump.append((char*)&length, sizeof(qint32));
    toDump.append(data);
    return toDump;
}
