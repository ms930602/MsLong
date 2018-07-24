function IsWindowShow_MSG(str)
    if (IsWindowShow(str)) then
        return 1
    end
    return 0
end

function SelectServer_MSG(Namestr)
	PushDebugMessage("正在查找服务器");
    local iCurAreaCount = GameProduceLogin:GetServerAreaCount();
    for index = 0, iCurAreaCount - 1 do
        local strAreaName = GameProduceLogin:GetServerAreaName(index);
        iLoginServerCount = GameProduceLogin:GetAreaLoginServerCount(index);
        for i = 0, iLoginServerCount - 1 do
            ServerName = GameProduceLogin:GetAreaLoginServerInfo(index, i);
            if Namestr == ServerName then
                GameProduceLogin:SelectLoginServer(index, i, 3);
            end
        end
    end
end

function LoginPassWord(username, mail)
    setmetatable(_G, { __index = LoginLogOn_Env });
    if this:IsVisible() then
        LogOn_LogonMailID_Active()
        LogOn_Region:SetCurrentSelect(tonumber(mail));
    end
    setmetatable(_G, { __index = LoginLogOn_Env });
    if this:IsVisible() then
        LogOn_LogonID_Active();
        LogOn_ID:SetText(tostring(username));
    end
    setmetatable(_G, { __index = LoginLogOn_Env });
    if this:IsVisible() then
        LogOn_LogonPassWord_Active();
        -- LogOn_PassWord:SetText("");
    end
end