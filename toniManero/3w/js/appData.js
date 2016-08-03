appData = function() {
    __data = function() {
        this.m_targetIp = "0.0.0.0";
        this.m_targetPort = 80;
        this.m_channelCount = 2;
        this.a_channelPwm = [50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50];
    }

    this.s_data = new __data();

    this.checkConfig = function() {
        var local = localStorage.getItem("toniManero.data");
        if (local === null) {
            return 0;
        } else {
            return 1;
        }
    }

    this.checkDefault = function() {
        if (this.s_data.m_targetIp == "0.0.0.0") {
            return 1;
        } else {
            return 0;
        }
    }

    this.load = function() {
        var js = localStorage.getItem("toniManero.data");
        this.s_data = JSON.parse(js);
    }

    this.save = function() {
        var js = JSON.stringify(this.s_data);
        localStorage.setItem("toniManero.data", js);
    }
}