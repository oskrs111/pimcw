qtkRtpCommand_* cmd;

cmd = new qtkRtpCommand_Test(this);
this->l_commands.append(cmd);

cmd = new qtkRtpCommand_PwmSet(this);
this->l_commands.append(cmd);

cmd = new qtkRtpCommand_ShellRun(this);
this->l_commands.append(cmd);

cmd = new qtkRtpCommand_pca9685Set(this);
this->l_commands.append(cmd);

cmd = new qtkRtpCommand_pca9685Get(this);
this->l_commands.append(cmd);

cmd = new qtkRtpCommand_pca9685GetAll(this);
this->l_commands.append(cmd);
