//
// Created by brd6 on 27/09/17.
//

#include "Client/ClientManager.hpp"

namespace ts
{
  void ClientManager::add(ClientPtr &client)
  {
    mClients.insert(client);
  }

  void ClientManager::remove(ClientPtr &client)
  {
    mClients.erase(client);
  }

  void ClientManager::stopAll()
  {
    std::for_each(std::begin(mClients), std::end(mClients),
		  [](auto &client) {
		    client->stop();
		  });
    mClients.clear();
  }

  void ClientManager::stop(ClientPtr &client)
  {
    client->stop();
  }

  void ClientManager::foreach(OnForeachFunc onForeach)
  {
    if (onForeach == nullptr)
      return;

    for (auto &it : mClients)
      {
	onForeach(it);
      }
  }
}
