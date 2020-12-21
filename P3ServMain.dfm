object Main: TMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'P3Serv'
  ClientHeight = 200
  ClientWidth = 400
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object PopupMenu: TPopupMenu
    Left = 224
    Top = 96
    object miCheck: TMenuItem
      Caption = #1055#1077#1088#1077#1076#1072#1090#1100' '#1076#1072#1085#1085#1099#1077
      Default = True
      OnClick = miCheckClick
    end
    object miSeparator01: TMenuItem
      Caption = '-'
    end
    object miOptions: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      OnClick = miOptionsClick
    end
    object miSeparator02: TMenuItem
      Caption = '-'
    end
    object miAbout: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = miAboutClick
    end
    object miSeparator03: TMenuItem
      Caption = '-'
    end
    object miClose: TMenuItem
      Caption = #1042#1099#1093#1086#1076
      OnClick = miCloseClick
    end
  end
  object TrayIcon: TTrayIcon
    PopupMenu = PopupMenu
    Visible = True
    OnClick = TrayIconClick
    Left = 32
    Top = 24
  end
  object ApplicationEvents: TApplicationEvents
    OnException = ApplicationEventsException
    Left = 176
    Top = 24
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 128
    Top = 104
  end
end
