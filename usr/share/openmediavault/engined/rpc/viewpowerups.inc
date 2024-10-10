<?php

/**
 * Copyright (C) 2013-2015 OpenMediaVault Plugin Developers
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

class OMVRpcServiceViewpowerups extends \OMV\Rpc\ServiceAbstract
{
    public function getName()
    {
        return 'viewpowerups';
    }

    public function initialize()
    {
        $this->registerMethod('getSettings');
        $this->registerMethod('setSettings');
        $this->registerMethod("getStats");
    }

    public function getSettings($params, $context)
    {
        // Validate the RPC caller context.
        $this->validateMethodContext($context, [ 'role' => OMV_ROLE_ADMINISTRATOR ]);

        $db = \OMV\Config\Database::getInstance();
        $object = $db->get('conf.service.viewpowerups');
        return $object->getAssoc();
    }

    public function setSettings($params, $context) {
        // Validate the RPC caller context.
        $this->validateMethodContext($context, ['role' => OMV_ROLE_ADMINISTRATOR]);
        // Validate the parameters of the RPC service method.
        $this->validateMethodParams($params, 'rpc.viewpowerups.setsettings');
        // Get the existing configuration object.
        $db = \OMV\Config\Database::getInstance();
        $object = $db->get('conf.service.viewpowerups');
        $object->setAssoc($params);
        // Set the configuration object.
        $db->set($object);
        // Return the configuration object.
        return $object->getAssoc();
    }

        /**
         * Get statistics, e.g. who's online.
         * @param params The method parameters.
         * @param context The context of the caller.
         * @return A string containing the requested statistics.
         */
        public function getStats($params, $context) {
                // Validate the RPC caller context.
                $this->validateMethodContext($context, [
                        "role" => OMV_ROLE_ADMINISTRATOR
                ]);
                // Is service enabled?
                $db = \OMV\Config\Database::getInstance();
                $object = $db->get("conf.service.viewpowerups");
                if (FALSE === $object->get("enable")) {
                        $stats = gettext("Service disabled");
                } else {
                        $mode = $object->get("urlViewPower");
                        $cmdArgs = [];
                        $cmd = new \OMV\System\Process("/etc/init.d/upsMonitor", "status");
                        $cmd->setRedirect2to1();
                        $cmd->execute($output);
                        $stats = implode("\n", $output);
                }
                return $stats;
        }
}
