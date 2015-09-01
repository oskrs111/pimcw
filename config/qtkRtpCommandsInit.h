qtkRtpCommand_Test* cmd;

cmd = new qtkRtpCommand_Test(this);
this->l_commands.append(cmd);

cmd = new qtkRtpCommand_PwmSet(this);
this->l_commands.append(cmd);
