/*
 *      Copyright (C) 2018-2019 Jean-Luc Barriere
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef PULSESTREAMER_H
#define PULSESTREAMER_H

#include "requestbroker.h"
#include "locked.h"

#define PULSESTREAMER_CNAME   "pulse"

namespace NSROOT
{

class PulseStreamer : public RequestBroker
{
public:
  PulseStreamer();
  ~PulseStreamer() { }
  virtual bool HandleRequest(void* handle, const char* uri) override;

  const char * CommonName() override { return PULSESTREAMER_CNAME; }
  RequestBroker::ResourcePtr GetResource(const std::string& title) override;
  RequestBroker::ResourceList GetResourceList() override;
  RequestBroker::ResourcePtr RegisterResource(const std::string& sourceUrl) override;
  void UnregisterResource(const std::string& uri) override;

private:
  ResourceList m_resources;

  // store current index of the pa sink
  LockedNumber<unsigned> m_sinkIndex;
  // count current running playback
  LockedNumber<int> m_playbackCount;

  std::string GetPASink();
  void FreePASink();
  void streamSink(void * handle);

  void Reply500(void * handle);
  void Reply400(void * handle);
  void Reply429(void * handle);
};

}

#endif /* PULSESTREAMER_H */
