//
// Created by brd6 on 27/09/17.
//


#ifndef _ClientManager_H_
# define _ClientManager_H_

#include <memory>
#include <set>
#include "Util/Singleton.hpp"
#include "Client.hpp"

namespace ts
{
  using OnForeachFunc = std::function<void(boost::shared_ptr<Client> client)>;

  class ClientManager
  {
   private:
    std::set<ClientPtr> mClients;

   public:
    //! Add new client
    //! \param client
    void add(ClientPtr &client);

    //! Remove client
    //! \param client
    void remove(ClientPtr &client);

    //! Stop a client
    //! \param client
    void stop(ClientPtr &client);

    //! Stop all client
    void stopAll();

    //! Apply a function on clients
    //! \param onForeach
    void foreach(OnForeachFunc onForeach);

  };
}

#endif /* !_ClientManager_H_ */