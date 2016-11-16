<?xml version="1.0" encoding="ASCII"?>
<alica:Plan xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:alica="http:///de.uni_kassel.vs.cn" id="1467396347588" name="RotationCalibration" comment="" masterPlan="true" utilityFunction="" utilityThreshold="0.1" destinationPath="Plans/Calibration" priority="0.0" minCardinality="0" maxCardinality="2147483647">
  <states id="1467396347589" name="Stop" comment="" entryPoint="1467396347590">
    <plans xsi:type="alica:BehaviourConfiguration">RotationCalibrationDeleteLogfile.beh#1479315306711</plans>
    <outTransitions>#1467396616225</outTransitions>
  </states>
  <states id="1467396438734" name="Rotating" comment="">
    <plans xsi:type="alica:BehaviourConfiguration">RotateOnce.beh#1467398000539</plans>
    <inTransitions>#1470237803234</inTransitions>
    <outTransitions>#1470227878581</outTransitions>
    <outTransitions>#1472656456600</outTransitions>
  </states>
  <states id="1470227765155" name="Finished" comment="">
    <plans xsi:type="alica:BehaviourConfiguration">../GenericBehaviours/Stop.beh#1413992626194</plans>
    <inTransitions>#1475074486547</inTransitions>
  </states>
  <states id="1470237789517" name="Return" comment="">
    <plans xsi:type="alica:BehaviourConfiguration">RestartMotion.beh#1472657588489</plans>
    <inTransitions>#1467396616225</inTransitions>
    <inTransitions>#1472656456600</inTransitions>
    <outTransitions>#1470237803234</outTransitions>
  </states>
  <states id="1475074211872" name="Calculation" comment="">
    <plans xsi:type="alica:BehaviourConfiguration">RotationCalibrationCalculation.beh#1475074454339</plans>
    <inTransitions>#1470227878581</inTransitions>
    <outTransitions>#1475074486547</outTransitions>
  </states>
  <transitions id="1467396616225" name="MISSING_NAME" comment="Status Start?" msg="">
    <preCondition id="1467396619848" name="MISSING_NAME" comment="" conditionString="" pluginName="DefaultPlugin" enabled="true"/>
    <inState>#1467396347589</inState>
    <outState>#1470237789517</outState>
  </transitions>
  <transitions id="1470227878581" name="MISSING_NAME" comment="Rotated often enough?" msg="">
    <preCondition id="1470227880114" name="MISSING_NAME" comment="" conditionString="" pluginName="DefaultPlugin" enabled="true"/>
    <inState>#1467396438734</inState>
    <outState>#1475074211872</outState>
  </transitions>
  <transitions id="1470237803234" name="MISSING_NAME" comment="INSTANT SUCCESS!!!" msg="">
    <preCondition id="1470237805501" name="MISSING_NAME" comment="" conditionString="" pluginName="DefaultPlugin" enabled="true"/>
    <inState>#1470237789517</inState>
    <outState>#1467396438734</outState>
  </transitions>
  <transitions id="1472656456600" name="MISSING_NAME" comment="finished rotation &amp;&amp; error too large" msg="">
    <preCondition id="1472656460039" name="MISSING_NAME" comment="" conditionString="" pluginName="DefaultPlugin" enabled="true"/>
    <inState>#1467396438734</inState>
    <outState>#1470237789517</outState>
  </transitions>
  <transitions id="1475074486547" name="MISSING_NAME" comment="Calculated RobotRadius and wrote config?" msg="">
    <preCondition id="1475074488561" name="MISSING_NAME" comment="" conditionString="" pluginName="DefaultPlugin" enabled="true"/>
    <inState>#1475074211872</inState>
    <outState>#1470227765155</outState>
  </transitions>
  <entryPoints id="1467396347590" name="MISSING_NAME" comment="" successRequired="false" minCardinality="0" maxCardinality="2147483647">
    <task>../../Misc/taskrepository.tsk#1225112227903</task>
    <state>#1467396347589</state>
  </entryPoints>
</alica:Plan>
