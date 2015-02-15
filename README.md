# vwiimote
----------

## Disable plugins
/etc/bluetooth/main.conf:  
`DisablePlugins = network,input,audio,pnat,sap,serial`

Restart bluetooth:  
`systemctl restart bluetooth`

## Check output
`sdptool browse local` must return nothing

## Dump
`sdptool records --xml`
