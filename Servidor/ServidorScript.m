clear, close all
joy1 = 0;
joy2 = 0;
t = tcpip('0.0.0.0', 30000, 'NetworkRole', 'server');
fopen(t);
t.BytesAvailableFcnMode = 'terminator';
t.BytesAvailableFcnCount = 'CR';
t.Terminator = "CR";
t.BytesAvailableFcn = @mycallback;

function mycallback(src,~)
% Read message
msg = fgetl(t);
display(msg)
msg = split(msg,','); 

if(strcmp(msg, 'SETJOY1'))

end