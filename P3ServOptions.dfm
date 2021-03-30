object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 372
  ClientWidth = 464
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    464
    372)
  PixelsPerInch = 96
  TextHeight = 21
  object btnOk: TButton
    Left = 258
    Top = 332
    Width = 96
    Height = 32
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 360
    Top = 332
    Width = 96
    Height = 32
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object PageControl: TPageControl
    Left = 8
    Top = 8
    Width = 450
    Height = 316
    ActivePage = tsMain
    MultiLine = True
    TabOrder = 0
    object tsMain: TTabSheet
      Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072
      object gbOptions: TGroupBox
        Left = 8
        Top = 8
        Width = 424
        Height = 88
        Caption = #1042#1093#1086#1076' '#1074' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
        TabOrder = 0
        object eOptionsPass: TLabeledEdit
          Left = 8
          Top = 48
          Width = 200
          Height = 29
          EditLabel.Width = 53
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1072#1088#1086#1083#1100
          PasswordChar = '#'
          TabOrder = 0
        end
        object eOptionsPass2: TLabeledEdit
          Left = 216
          Top = 48
          Width = 200
          Height = 29
          EditLabel.Width = 116
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1086#1076#1090#1074#1077#1088#1078#1076#1077#1085#1080#1077
          PasswordChar = '#'
          TabOrder = 1
        end
      end
      object rgProgramMode: TRadioGroup
        Left = 8
        Top = 96
        Width = 208
        Height = 150
        Caption = #1058#1080#1087' '#1084#1086#1076#1091#1083#1103
        TabOrder = 1
      end
      object gbTimer: TGroupBox
        Left = 224
        Top = 96
        Width = 208
        Height = 150
        Caption = #1058#1072#1081#1084#1077#1088' '#1086#1090#1087#1088#1072#1074#1082#1080
        TabOrder = 2
        object lblTimerPeriodStart: TLabel
          Left = 8
          Top = 84
          Width = 112
          Height = 21
          Caption = #1053#1072#1095#1072#1083#1086' '#1086#1090#1089#1095#1105#1090#1072
          FocusControl = seTimerPeriodStart
        end
        object lblTimerPeriod: TLabel
          Left = 8
          Top = 24
          Width = 113
          Height = 21
          Caption = #1055#1077#1088#1080#1086#1076#1080#1095#1085#1086#1089#1090#1100
          FocusControl = cboxTimerPeriod
        end
        object cboxTimerPeriod: TComboBox
          Left = 8
          Top = 48
          Width = 192
          Height = 29
          Style = csDropDownList
          TabOrder = 0
        end
        object seTimerPeriodStart: TSpinEdit
          Left = 8
          Top = 108
          Width = 192
          Height = 31
          MaxValue = 59
          MinValue = 0
          TabOrder = 1
          Value = 0
        end
      end
    end
    object tsMySQL: TTabSheet
      Caption = 'MySQL'
      ImageIndex = 1
      object gbMySQL: TGroupBox
        Left = 8
        Top = 8
        Width = 424
        Height = 188
        Caption = #1055#1086#1076#1082#1083#1102#1095#1077#1085#1080#1077
        TabOrder = 0
        object eMySQLHost: TLabeledEdit
          Left = 8
          Top = 48
          Width = 408
          Height = 29
          EditLabel.Width = 147
          EditLabel.Height = 21
          EditLabel.Caption = #1040#1076#1088#1077#1089' '#1080#1083#1080' '#1080#1084#1103' '#1093#1086#1089#1090#1072
          TabOrder = 0
        end
        object eMySQLUser: TLabeledEdit
          Left = 8
          Top = 108
          Width = 200
          Height = 29
          EditLabel.Width = 44
          EditLabel.Height = 21
          EditLabel.Caption = #1051#1086#1075#1080#1085
          TabOrder = 1
        end
        object eMySQLPass: TLabeledEdit
          Left = 216
          Top = 108
          Width = 200
          Height = 29
          EditLabel.Width = 53
          EditLabel.Height = 21
          EditLabel.Caption = #1055#1072#1088#1086#1083#1100
          PasswordChar = '#'
          TabOrder = 2
        end
        object btnCheckMySQL: TButton
          Left = 8
          Top = 146
          Width = 96
          Height = 32
          Caption = #1055#1088#1086#1074#1077#1088#1082#1072
          TabOrder = 3
          OnClick = btnCheckMySQLClick
        end
      end
    end
    object tsAglodoza: TTabSheet
      Caption = #1040#1075#1083#1086#1076#1086#1079#1080#1088#1086#1074#1082#1072
      ImageIndex = 2
      object eAglodozaScaleNum: TLabeledEdit
        Left = 8
        Top = 32
        Width = 121
        Height = 29
        EditLabel.Width = 92
        EditLabel.Height = 21
        EditLabel.Caption = #1053#1086#1084#1077#1088' '#1074#1077#1089#1086#1074
        TabOrder = 0
      end
      object eAglodozaDatabase: TLabeledEdit
        Left = 8
        Top = 92
        Width = 386
        Height = 29
        EditLabel.Width = 89
        EditLabel.Height = 21
        EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        TabOrder = 1
      end
      object btnAglodozaDatabase: TButton
        Left = 404
        Top = 92
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 2
        OnClick = btnAglodozaDatabaseClick
      end
      object btnCheckAglodoza: TButton
        Left = 8
        Top = 132
        Width = 96
        Height = 32
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072
        TabOrder = 3
        OnClick = btnCheckMySQLClick
      end
    end
    object tsKoksohim: TTabSheet
      Caption = #1044#1086#1079#1072#1090#1086#1088#1099' '#1050#1061#1055
      ImageIndex = 3
      object eKoksohimScaleNum: TLabeledEdit
        Left = 8
        Top = 32
        Width = 121
        Height = 29
        EditLabel.Width = 92
        EditLabel.Height = 21
        EditLabel.Caption = #1053#1086#1084#1077#1088' '#1074#1077#1089#1086#1074
        TabOrder = 0
      end
      object eKoksohimDatabase: TLabeledEdit
        Left = 8
        Top = 92
        Width = 386
        Height = 29
        EditLabel.Width = 89
        EditLabel.Height = 21
        EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        TabOrder = 1
      end
      object btnCheckKoksohim: TButton
        Left = 8
        Top = 132
        Width = 96
        Height = 32
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072
        TabOrder = 3
        Visible = False
        OnClick = btnCheckMySQLClick
      end
      object btnKoksohimDatabase: TButton
        Left = 404
        Top = 92
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 2
        OnClick = btnAglodozaDatabaseClick
      end
    end
    object tsDomna: TTabSheet
      Caption = #1044#1086#1084#1077#1085#1085#1072#1103' '#1087#1077#1095#1100
      ImageIndex = 4
      object eDomnaScaleNum: TLabeledEdit
        Left = 8
        Top = 32
        Width = 121
        Height = 29
        EditLabel.Width = 92
        EditLabel.Height = 21
        EditLabel.Caption = #1053#1086#1084#1077#1088' '#1074#1077#1089#1086#1074
        TabOrder = 0
      end
      object eDomnaDatabase: TLabeledEdit
        Left = 8
        Top = 92
        Width = 386
        Height = 29
        EditLabel.Width = 89
        EditLabel.Height = 21
        EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        TabOrder = 1
      end
      object btnCheckDomna: TButton
        Left = 8
        Top = 192
        Width = 96
        Height = 32
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072
        TabOrder = 3
        OnClick = btnCheckMySQLClick
      end
      object btnDomnaDatabase: TButton
        Left = 404
        Top = 92
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 2
        OnClick = btnAglodozaDatabaseClick
      end
      object eDomnaPass: TLabeledEdit
        Left = 8
        Top = 152
        Width = 200
        Height = 29
        EditLabel.Width = 53
        EditLabel.Height = 21
        EditLabel.Caption = #1055#1072#1088#1086#1083#1100
        PasswordChar = '#'
        TabOrder = 4
      end
      object cboxHumidity: TCheckBox
        Left = 144
        Top = 38
        Width = 97
        Height = 17
        Caption = #1042#1083#1072#1078#1085#1086#1089#1090#1100
        TabOrder = 5
      end
    end
    object tsKanat: TTabSheet
      Caption = #1050#1072#1085#1072#1090#1085#1072#1103' '#1076#1086#1088#1086#1075#1072
      ImageIndex = 2
      object eKanatScaleNum: TLabeledEdit
        Left = 8
        Top = 32
        Width = 121
        Height = 29
        EditLabel.Width = 92
        EditLabel.Height = 21
        EditLabel.Caption = #1053#1086#1084#1077#1088' '#1074#1077#1089#1086#1074
        TabOrder = 0
      end
      object eKanatDatabase: TLabeledEdit
        Left = 8
        Top = 92
        Width = 386
        Height = 29
        EditLabel.Width = 89
        EditLabel.Height = 21
        EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        TabOrder = 1
      end
      object btnKanatDatabase: TButton
        Left = 404
        Top = 92
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 2
        OnClick = btnAglodozaDatabaseClick
      end
      object btnCheckKanat: TButton
        Left = 8
        Top = 132
        Width = 96
        Height = 32
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072
        TabOrder = 3
        OnClick = btnCheckMySQLClick
      end
    end
    object tsWD30: TTabSheet
      Caption = #1046#1044' '#1074#1077#1089#1099' '#1042#1044'-30'
      ImageIndex = 6
      object eWD30ScaleNum: TLabeledEdit
        Left = 8
        Top = 32
        Width = 121
        Height = 29
        EditLabel.Width = 92
        EditLabel.Height = 21
        EditLabel.Caption = #1053#1086#1084#1077#1088' '#1074#1077#1089#1086#1074
        TabOrder = 0
      end
      object eWD30Logs: TLabeledEdit
        Left = 8
        Top = 92
        Width = 386
        Height = 29
        EditLabel.Width = 149
        EditLabel.Height = 21
        EditLabel.Caption = #1056#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1077' '#1083#1086#1075#1086#1074
        TabOrder = 1
      end
      object btnCheckWD30: TButton
        Left = 8
        Top = 132
        Width = 96
        Height = 32
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072
        TabOrder = 3
        Visible = False
        OnClick = btnCheckMySQLClick
      end
      object btnWD30Logs: TButton
        Left = 404
        Top = 92
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 2
        OnClick = btnWD30LogsClick
      end
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'mdb'
    Filter = 
      #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093'|*.mdb;*.dbf|'#1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093' Microsoft Access|*.mdb|'#1041#1072#1079#1072' ' +
      #1076#1072#1085#1085#1099#1093' DBF|*.dbf|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing, ofDontAddToRecent]
    Left = 150
    Top = 262
  end
end
