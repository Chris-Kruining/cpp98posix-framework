#include "Observable.h"

namespace Event
{
  Observable::Observable()
  {
  }

  Observable::~Observable()
  {
  }

  void Observable::Attach(IObserver* observer)
  {
    this->observers.push_back(observer);
  }

  void Observable::Fire(string eventName, IEventArgs* args)
  {
    for(unsigned int i = 0; i < this->observers.size(); i++)
    {
      if(this->IsInNamespace(this->observers[i], eventName))
      {
        int id = Threading::ThreadManager::SpawnThread(this->observers[i], &IObserver::Update, args);

        if(id < 0)
        {
          cout << "oops, spawning threads is tough..." << endl;
        }
      }
    }

    usleep(10); // workaround to give ThreadManager the time to copy the eventargs...
  }

  bool Observable::IsInNamespace(IObserver* observer, string eventName)
  {
    vector<string> observerParts = String::Split(observer->GetEventName(), '.');
    vector<string> eventNameParts = String::Split(eventName, '.');

    if(observerParts.size() > eventNameParts.size() && !String::Contains(eventNameParts, "*"))
    {
      return false;
    }

    int found = -1;
    unsigned int eventNameIndex = 0;

    for(unsigned int i = 0; i < observerParts.size(); i++)
    {
      if(eventNameIndex >= eventNameParts.size())
      {
        break;
      }

      if(observerParts[i] == "+" || eventNameParts[eventNameIndex] == "+")
      {
        found = i;
      }
      else if(observerParts[i] == "*")
      {
        if(i + 1 >= observerParts.size())
        {
          found = i;
          break;
        }

        for(unsigned int j = eventNameIndex; j < eventNameParts.size(); j++)
        {
          if(eventNameParts[j] == observerParts[i + 1])
          {
            eventNameIndex = j - 1;
            break;
          }
        }

        found = -1;
      }
      else if(eventNameParts[eventNameIndex] == "*")
      {
        cout << "TODO :: eventNameParts *" << endl;
        return false;
      }
      else
      {
        if(observerParts[i].compare(eventNameParts[eventNameIndex]) == 0)
        {
          found = i;
        }
        else
        {
          found = -1;
        }
      }

      eventNameIndex++;
    }

    return found != -1;
  }
}
