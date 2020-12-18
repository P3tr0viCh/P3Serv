object frmLogin: TfrmLogin
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1042#1093#1086#1076' '#1074' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 124
  ClientWidth = 232
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 21
  object btnOk: TButton
    Left = 16
    Top = 79
    Width = 96
    Height = 32
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 120
    Top = 79
    Width = 96
    Height = 32
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object ePass: TLabeledEdit
    Left = 16
    Top = 32
    Width = 200
    Height = 29
    EditLabel.Width = 53
    EditLabel.Height = 21
    EditLabel.Caption = #1055#1072#1088#1086#1083#1100
    PasswordChar = '#'
    TabOrder = 0
  end
end
