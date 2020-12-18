object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 352
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
    352)
  PixelsPerInch = 96
  TextHeight = 21
  object btnOk: TButton
    Left = 258
    Top = 312
    Width = 96
    Height = 32
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    TabOrder = 0
    OnClick = btnOkClick
    ExplicitLeft = 232
    ExplicitTop = 329
  end
  object btnCancel: TButton
    Left = 360
    Top = 312
    Width = 96
    Height = 32
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 1
    ExplicitLeft = 334
    ExplicitTop = 329
  end
  object PageControl: TPageControl
    Left = 8
    Top = 8
    Width = 450
    Height = 294
    ActivePage = tsDomna
    MultiLine = True
    TabOrder = 2
    object tsMain: TTabSheet
      Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072
      ExplicitTop = 32
      ExplicitWidth = 441
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
        Height = 128
        Caption = #1058#1080#1087' '#1084#1086#1076#1091#1083#1103
        Items.Strings = (
          #1040#1075#1083#1086#1076#1086#1079#1080#1088#1086#1074#1082#1072
          #1044#1086#1079#1072#1090#1086#1088#1099' '#1050#1061#1055
          #1044#1086#1084#1077#1085#1085#1072#1103' '#1087#1077#1095#1100)
        TabOrder = 1
      end
    end
    object tsMySQL: TTabSheet
      Caption = 'MySQL'
      ImageIndex = 1
      ExplicitTop = 32
      ExplicitWidth = 441
      object gbMySQL: TGroupBox
        Left = 8
        Top = 8
        Width = 424
        Height = 192
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
          Top = 112
          Width = 200
          Height = 29
          EditLabel.Width = 44
          EditLabel.Height = 21
          EditLabel.Caption = #1051#1086#1075#1080#1085
          TabOrder = 1
        end
        object eMySQLPass: TLabeledEdit
          Left = 216
          Top = 112
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
          Top = 150
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
      ExplicitTop = 32
      ExplicitWidth = 441
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
        Top = 96
        Width = 386
        Height = 29
        EditLabel.Width = 89
        EditLabel.Height = 21
        EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        TabOrder = 1
      end
      object btnAglodozaDatabase: TButton
        Left = 404
        Top = 96
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 2
        OnClick = btnAglodozaDatabaseClick
      end
      object btnCheckAglodoza: TButton
        Left = 8
        Top = 136
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
      ExplicitTop = 32
      ExplicitWidth = 441
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
        Top = 96
        Width = 386
        Height = 29
        EditLabel.Width = 89
        EditLabel.Height = 21
        EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        TabOrder = 1
      end
      object btnCheckKoksohim: TButton
        Left = 8
        Top = 136
        Width = 96
        Height = 32
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072
        TabOrder = 2
        OnClick = btnCheckMySQLClick
      end
      object btnKoksohimDatabase: TButton
        Left = 404
        Top = 96
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 3
        OnClick = btnAglodozaDatabaseClick
      end
    end
    object tsDomna: TTabSheet
      Caption = #1044#1086#1084#1077#1085#1085#1072#1103' '#1087#1077#1095#1100
      ImageIndex = 4
      ExplicitWidth = 441
      ExplicitHeight = 206
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
        Top = 96
        Width = 386
        Height = 29
        EditLabel.Width = 89
        EditLabel.Height = 21
        EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        TabOrder = 1
      end
      object btnCheckDomna: TButton
        Left = 8
        Top = 136
        Width = 96
        Height = 32
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072
        TabOrder = 2
        OnClick = btnCheckMySQLClick
      end
      object btnDomnaDatabase: TButton
        Left = 404
        Top = 96
        Width = 30
        Height = 29
        Caption = '...'
        TabOrder = 3
        OnClick = btnAglodozaDatabaseClick
      end
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'mdb'
    Filter = 
      #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093'|*.mdb;*.dbf|'#1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093' Microsoft Access|*.mdb|'#1041#1072#1079#1072' ' +
      #1076#1072#1085#1085#1099#1093' DBF|*.dbf|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing, ofDontAddToRecent]
    Left = 334
    Top = 214
  end
end
