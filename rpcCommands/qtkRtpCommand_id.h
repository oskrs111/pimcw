#ifndef QTKRTPCOMMAND_ID__H
#define QTKRTPCOMMAND_ID__H
//OSLL: Define here the id's for your RPC commands as well it's text names, or 'alias'. 
//--> {"jsonrpc": "2.0", "method": "subtract", "params": {"subtrahend": 23, "minuend": 42}, "id": 3}
//<-- {"jsonrpc": "2.0", "result": 19, "id": 3}

#define RCI_BASE 100
namespace k_rtp_command_id
{
	enum 
	{		
        rci_TestCommand = RCI_BASE,
        rci_PwmSetCommand,
        rci_pca9685SetCommand,
        rci_pca9685GetCommand,
		rci_Last	
	};


struct rtpCommandStruct
{
	char* p_commandAlias;
	int m_commandId;
};

static struct rtpCommandStruct rtpCommands [] =
{
{"test", rci_TestCommand},
{"pwmSet", rci_PwmSetCommand},
{"pca9685Set", rci_pca9685SetCommand},
{"pca9685Get", rci_pca9685GetCommand}
};


}
#endif 
