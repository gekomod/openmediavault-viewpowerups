<?php
/**
 * Copyright (C) 2022-2024 OpenMediaVault Plugin Developers
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
class OMVRpcServiceViewPowerStat extends \OMV\Rpc\ServiceAbstract
{
    public function getName()
    {
        return "ViewPowerStat";
    }

    public function initialize()
    {
        $this->registerMethod("getStats");
        $this->registerMethod("getBatteryCapacityStats");
    }

    public function getStats($params, $context)
    {
        // Validate the RPC caller context.
        $this->validateMethodContext($context, ["role" => OMV_ROLE_EVERYONE]);
        $output = [];

                $db = \OMV\Config\Database::getInstance();
                $object = $db->get("conf.service.viewpowerups");
		$url = $object->get("urlViewPower");

                if (FALSE === $object->get("enable")) {
                        $temps = gettext("Service disabled");
                } else {

$obj = json_decode(file_get_contents($url), true);

$workinfo = $obj['workInfo']['batteryVoltage'];
$workmode = $obj['workInfo']['workMode'];
$batteryCapacity = $obj['workInfo']['batteryCapacity'];
if($obj['workInfo']['chargeON'] == false) { $chargeON = '<span style="color:red">Brak Ładowania</span>'; } else { $chargeOn = '<span style="color:green">Ładowanie Baterii</span>'; }
$inputVoltage = $obj['workInfo']['inputVoltage'];
$outputLoadPercent = (int) $obj['workInfo']['outputLoadPercent'];
$outputVoltage = $obj['workInfo']['outputVoltage'];
$outputFrequency = $obj['workInfo']['outputFrequency'];

$temps = '
<section style="position: relative; margin-left: 1%;">
	<article>
		<table class ="fl">
			<tr>
				<td valign="top" >
					<article style="padding: 25px 0 0 25px;">
						<div id="statusinfo" style="min-width:500px;max-width:700px">
								<h3>
									Informacja wejściowa
								</h3>
								<table style="min-width:500px;max-width:700px">
									<tr><td>Napięcie wejściowe:</td><td>'.$inputVoltage.'</td><td>V</td></tr>
								</table>
							
								<h3>
									Informacja o UPS
								</h3>
								<table style="min-width:500px;max-width:700px">
									<tr><td>Tryb UPS:</td><td>'.$workmode.'</td><td></td></tr>
								</table>
							
								<h3>
									Informacja o akumulatorze
								</h3>
								<table style="min-width:500px;max-width:700px">
									<tr><td>Napięcie akumulatora:</td><td>'.$workinfo.'</td><td>V</td></tr>
									<tr><td>Pojemność akumulatora:</td><td>'.$batteryCapacity.'</td><td>%</td></tr>
                                    <tr><td>Tryb Ładowania:</td><td>'.$chargeON.'</td><td></td></tr>
								</table>
							
								<h3>
									Informacja z wyjścia
								</h3>
								<table style="min-width:500px;max-width:700px">
									<tr><td>Napięcie wyjściowe:</td><td>'.$outputVoltage.'</td><td>V</td></tr>
									<tr><td>Częstotliwość wyjściowa:</td><td>'.$outputFrequency.'</td><td>Hz</td></tr>
									<tr><td>Poziom obciążenia:</td><td>'.$outputLoadPercent.'</td><td>%</td></tr>
								</table>
						</div>
					</article>
				</td>
			</tr>
		</table>
	</article>
</section>';

}
        return ($temps);
    }

    public function getBatteryCapacityStats($params, $context)
    {
        $db = \OMV\Config\Database::getInstance();
        $object = $db->get("conf.service.viewpowerups");
        $url = $object->get("urlViewPower");

        if (FALSE === $object->get("enable")) {
               $result = gettext("Service disabled");
        } else {
               $obj = json_decode(file_get_contents($url), true);
               // Validate the RPC caller context.
	       $this->validateMethodContext($context, [
                       "role" => OMV_ROLE_ADMINISTRATOR
	       ]);
        $data = ['batteryCapacity' => ''.$obj['workInfo']['batteryCapacity'].'', 'enable'=>'true'];
        $result = $data;
        }
	return $result;
    }

}
