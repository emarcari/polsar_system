/*!
  \file LoadModules.h
 
  \brief Load terralib modules.
 */

#include <common.h>
#include <plugin.h>
#include <Config.h>

/*!
  \brief Load TerraLib modules.
 */

void LoadModules()
{
  std::string plugins_path = te::common::FindInTerraLibPath("share/terralib/plugins");

  te::plugin::PluginInfo* info;
  
#ifdef TERRALIB_MOD_OGR_ENABLED
  info = te::plugin::GetInstalledPlugin(plugins_path + "/te.da.ogr.teplg");
  te::plugin::PluginManager::getInstance().add(info); 
#endif

#ifdef TERRALIB_MOD_GDAL_ENABLED
  info = te::plugin::GetInstalledPlugin(plugins_path + "/te.da.gdal.teplg");
  te::plugin::PluginManager::getInstance().add(info);
#endif

  te::plugin::PluginManager::getInstance().loadAll();  
}
