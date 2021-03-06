/*
 * Copyright (C) 2011  Ives van der Flaas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Poco/Thread.h"
#include "Bacsy/Server/BacsyServer.h"
#include "Bacsy/Client/BackupEngine.h"
#include "Bacsy/Server/MulticastResponder.h"
#include "Bacsy/Common/CascadingFileConfiguration.h"
#include "Bacsy/Client/Source.h"
#include "Bacsy/Common/ConfigurationFile.h"

using namespace Bacsy;

int main()
{
	CascadingFileConfiguration configuration(".bacsy");

	if(!configuration.sourceFileLoaded())
	{
		LOGF("No .bacsy/sources.config file found.");
	}

	if(!configuration.storesFileLoaded())
	{
		LOGF("No .bacsy/stores.config file found.");
	}

	StoreManager storeManager(configuration);

	BacsyServer server(storeManager);
	server.start();

	BackupEngine backupEngine(configuration);
	backupEngine.start();
	
	MulticastResponder responder;
	responder.start();

	while(true)
		Poco::Thread::sleep(10000);
}
