#! /bin/bash

echo "Script de prueba crea dos interfaces frc-est1 frc-est2."
echo "Usadlas para probar la práctica."
echo "Lanzad una de las instancias de la aplicación en este terminal"
echo "Una vez terminéis para cerrar el terminal escribid exit "


ip netns add h1
ip link add frc-est1 type veth peer name frc-est2
ip link set frc-est1 netns h1
ip link set frc-est2 up
ip netns exec h1 ip link set dev frc-est1 up
ip netns exec h1 bash


ip link del frc-est2
ip netns del h1

