#include "ISocket.h"
namespace ShitHTTP {
	class IFactory {
	public:
		virtual ISocket* openSocket(int port);
	};
}
