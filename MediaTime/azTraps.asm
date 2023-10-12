; Version: 1.08
; Created: Wednesday, October 19, 1988 at 2:06:04 PM
;
; File: Traps.a
;
; Assembler Interface to the Macintosh Libraries
; Copyright Apple Computer, Inc. 1984-1988
; All Rights Reserved
;___________________________________________________________________________
; Equates for setting trap option bits
immed			EQU 		$200					; execute immediately, bypass I/O queue
clear			EQU 		$200					;
async			EQU 		$400					; asynchronous, don't wait for completion
sys 			EQU 		$400					;
autoPop 		EQU 		$400					; set autopop bit
; for string routines
marks			EQU 		$200					; set to ignore/strip diacriticals
case			EQU 		$400					; set for case sensitivity
; for Get/Set & NGet/NSet TrapAddress
newTool 		EQU 		$0600					; tool trap, under new ordering
newOS			EQU 		$0200					; os trap, under new ordering
; QuickDraw Traps
				MACRO		_CopyMask				
				DC.W		$A817
				ENDM
				MACRO		_MeasureText			
				DC.W		$A837
				ENDM
				MACRO		_GetMaskTable			
				DC.W		$A836
				ENDM
				MACRO		_CalcMask				
				DC.W		$A838
				ENDM
				MACRO		_SeedFill				
				DC.W		$A839
				ENDM
				MACRO		_InitCursor 			
				DC.W		$A850
				ENDM
				MACRO		_SetCursor				
				DC.W		$A851
				ENDM
				MACRO		_HideCursor 			
				DC.W		$A852
				ENDM
				MACRO		_ShowCursor 			
				DC.W		$A853
				ENDM
				MACRO		_ShieldCursor			
				DC.W		$A855
				ENDM
				MACRO		_ObscureCursor			
				DC.W		$A856
				ENDM
				MACRO		_BitAnd 				
				DC.W		$A858
				ENDM
				MACRO		_BitXOr 				
				DC.W		$A859
				ENDM
				MACRO		_BitNot 				
				DC.W		$A85A
				ENDM
				MACRO		_BitOr					
				DC.W		$A85B
				ENDM
				MACRO		_BitShift				
				DC.W		$A85C
				ENDM
				MACRO		_BitTst 				
				DC.W		$A85D
				ENDM
				MACRO		_BitSet 				
				DC.W		$A85E
				ENDM
				MACRO		_BitClr 				
				DC.W		$A85F
				ENDM
				MACRO		_Random 				
				DC.W		$A861
				ENDM
				MACRO		_ForeColor				
				DC.W		$A862
				ENDM
				MACRO		_BackColor				
				DC.W		$A863
				ENDM
				MACRO		_ColorBit				
				DC.W		$A864
				ENDM
				MACRO		_GetPixel				
				DC.W		$A865
				ENDM
				MACRO		_StuffHex				
				DC.W		$A866
				ENDM
				MACRO		_LongMul				
				DC.W		$A867
				ENDM
				MACRO		_FixMul 				
				DC.W		$A868
				ENDM
				MACRO		_FixRatio				
				DC.W		$A869
				ENDM
				MACRO		_HiWord 				
				DC.W		$A86A
				ENDM
				MACRO		_LoWord 				
				DC.W		$A86B
				ENDM
				MACRO		_FixRound				
				DC.W		$A86C
				ENDM
				MACRO		_InitPort				
				DC.W		$A86D
				ENDM
				MACRO		_InitGraf				
				DC.W		$A86E
				ENDM
				MACRO		_OpenPort				
				DC.W		$A86F
				ENDM
				MACRO		_LocalToGlobal			
				DC.W		$A870
				ENDM
				MACRO		_GlobalToLocal			
				DC.W		$A871
				ENDM
				MACRO		_GrafDevice 			
				DC.W		$A872
				ENDM
				MACRO		_SetPort				
				DC.W		$A873
				ENDM
				MACRO		_GetPort				
				DC.W		$A874
				ENDM
				MACRO		_SetPBits				
				DC.W		$A875
				ENDM
				MACRO		_PortSize				
				DC.W		$A876
				ENDM
				MACRO		_MovePortTo 			
				DC.W		$A877
				ENDM
				MACRO		_SetOrigin				
				DC.W		$A878
				ENDM
				MACRO		_SetClip				
				DC.W		$A879
				ENDM
				MACRO		_GetClip				
				DC.W		$A87A
				ENDM
				MACRO		_ClipRect				
				DC.W		$A87B
				ENDM
				MACRO		_BackPat				
				DC.W		$A87C
				ENDM
				MACRO		_ClosePort				
				DC.W		$A87D
				ENDM
				MACRO		_AddPt					
				DC.W		$A87E
				ENDM
				MACRO		_SubPt					
				DC.W		$A87F
				ENDM
				MACRO		_SetPt					
				DC.W		$A880
				ENDM
				MACRO		_EqualPt				
				DC.W		$A881
				ENDM
				MACRO		_StdText				
				DC.W		$A882
				ENDM
				MACRO		_DrawChar				
				DC.W		$A883
				ENDM
				MACRO		_DrawString 			
				DC.W		$A884
				ENDM
				MACRO		_DrawText				
				DC.W		$A885
				ENDM
				MACRO		_TextWidth				
				DC.W		$A886
				ENDM
				MACRO		_TextFont				
				DC.W		$A887
				ENDM
				MACRO		_TextFace				
				DC.W		$A888
				ENDM
				MACRO		_TextMode				
				DC.W		$A889
				ENDM
				MACRO		_TextSize				
				DC.W		$A88A
				ENDM
				MACRO		_GetFontInfo			
				DC.W		$A88B
				ENDM
				MACRO		_StringWidth			
				DC.W		$A88C
				ENDM
				MACRO		_CharWidth				
				DC.W		$A88D
				ENDM
				MACRO		_SpaceExtra 			
				DC.W		$A88E
				ENDM
				MACRO		_StdLine				
				DC.W		$A890
				ENDM
				MACRO		_LineTo 				
				DC.W		$A891
				ENDM
				MACRO		_Line					
				DC.W		$A892
				ENDM
				MACRO		_MoveTo 				
				DC.W		$A893
				ENDM
				MACRO		_Move					
				DC.W		$A894
				ENDM
				MACRO		_ShutDown				
				DC.W		$A895
				ENDM
				MACRO		_sdPowerOff	;9-18-90 JWH
				MOVE		#1,-(SP)				
				_ShutDown
				ENDM
				MACRO		_sdRestart	;9-18-90 JWH
				MOVE		#2,-(SP)				
				_ShutDown
				ENDM
				MACRO		_HidePen				
				DC.W		$A896
				ENDM
				MACRO		_ShowPen				
				DC.W		$A897
				ENDM
				MACRO		_GetPenState			
				DC.W		$A898
				ENDM
				MACRO		_SetPenState			
				DC.W		$A899
				ENDM
				MACRO		_GetPen 				
				DC.W		$A89A
				ENDM
				MACRO		_PenSize				
				DC.W		$A89B
				ENDM
				MACRO		_PenMode				
				DC.W		$A89C
				ENDM
				MACRO		_PenPat 				
				DC.W		$A89D
				ENDM
				MACRO		_PenNormal				
				DC.W		$A89E
				ENDM
				MACRO		_Unimplemented			
				DC.W		$A89F
				ENDM
				MACRO		_StdRect				
				DC.W		$A8A0
				ENDM
				MACRO		_FrameRect				
				DC.W		$A8A1
				ENDM
				MACRO		_PaintRect				
				DC.W		$A8A2
				ENDM
				MACRO		_EraseRect				
				DC.W		$A8A3
				ENDM
				MACRO		_InverRect				
				DC.W		$A8A4
				ENDM
				MACRO		_FillRect				
				DC.W		$A8A5
				ENDM
				MACRO		_EqualRect				
				DC.W		$A8A6
				ENDM
				MACRO		_SetRect				
				DC.W		$A8A7
				ENDM
				MACRO		_OffSetRect 			
				DC.W		$A8A8
				ENDM
				MACRO		_InSetRect				
				DC.W		$A8A9
				ENDM
				MACRO		_SectRect				
				DC.W		$A8AA
				ENDM
				MACRO		_UnionRect				
				DC.W		$A8AB
				ENDM
				MACRO		_Pt2Rect				
				DC.W		$A8AC
				ENDM
				MACRO		_PtInRect				
				DC.W		$A8AD
				ENDM
				MACRO		_EmptyRect				
				DC.W		$A8AE
				ENDM
				MACRO		_StdRRect				
				DC.W		$A8AF
				ENDM
				MACRO		_FrameRoundRect   		
				DC.W		$A8B0
				ENDM
				MACRO		_PaintRoundRect   		
				DC.W		$A8B1
				ENDM
				MACRO		_EraseRoundRect   		
				DC.W		$A8B2
				ENDM
				MACRO		_InverRoundRect   		
				DC.W		$A8B3
				ENDM
				MACRO		_FillRoundRect			
				DC.W		$A8B4
				ENDM
				MACRO		_StdOval				
				DC.W		$A8B6
				ENDM
				MACRO		_FrameOval				
				DC.W		$A8B7
				ENDM
				MACRO		_PaintOval				
				DC.W		$A8B8
				ENDM
				MACRO		_EraseOval				
				DC.W		$A8B9
				ENDM
				MACRO		_InvertOval 			
				DC.W		$A8BA
				ENDM
				MACRO		_FillOval				
				DC.W		$A8BB
				ENDM
				MACRO		_SlopeFromAngle   		
				DC.W		$A8BC
				ENDM
				MACRO		_StdArc 				
				DC.W		$A8BD
				ENDM
				MACRO		_FrameArc				
				DC.W		$A8BE
				ENDM
				MACRO		_PaintArc				
				DC.W		$A8BF
				ENDM
				MACRO		_EraseArc				
				DC.W		$A8C0
				ENDM
				MACRO		_InvertArc				
				DC.W		$A8C1
				ENDM
				MACRO		_FillArc				
				DC.W		$A8C2
				ENDM
				MACRO		_PtToAngle				
				DC.W		$A8C3
				ENDM
				MACRO		_AngleFromSlope   		
				DC.W		$A8C4
				ENDM
				MACRO		_StdPoly				
				DC.W		$A8C5
				ENDM
				MACRO		_FramePoly				
				DC.W		$A8C6
				ENDM
				MACRO		_PaintPoly				
				DC.W		$A8C7
				ENDM
				MACRO		_ErasePoly				
				DC.W		$A8C8
				ENDM
				MACRO		_InvertPoly 			
				DC.W		$A8C9
				ENDM
				MACRO		_FillPoly				
				DC.W		$A8CA
				ENDM
				MACRO		_OpenPoly				
				DC.W		$A8CB
				ENDM
				MACRO		_ClosePgon				
				DC.W		$A8CC
				ENDM
				MACRO		_KillPoly				
				DC.W		$A8CD
				ENDM
				MACRO		_OffSetPoly 			
				DC.W		$A8CE
				ENDM
				MACRO		_PackBits				
				DC.W		$A8CF
				ENDM
				MACRO		_UnpackBits 			
				DC.W		$A8D0
				ENDM
				MACRO		_StdRgn 				
				DC.W		$A8D1
				ENDM
				MACRO		_FrameRgn				
				DC.W		$A8D2
				ENDM
				MACRO		_PaintRgn				
				DC.W		$A8D3
				ENDM
				MACRO		_EraseRgn				
				DC.W		$A8D4
				ENDM
				MACRO		_InverRgn				
				DC.W		$A8D5
				ENDM
				MACRO		_FillRgn				
				DC.W		$A8D6
				ENDM
				MACRO		_NewRgn 				
				DC.W		$A8D8
				ENDM
				MACRO		_DisposRgn				
				DC.W		$A8D9
				ENDM
				MACRO		_OpenRgn				
				DC.W		$A8DA
				ENDM
				MACRO		_CloseRgn				
				DC.W		$A8DB
				ENDM
				MACRO		_CopyRgn				
				DC.W		$A8DC
				ENDM
				MACRO		_SetEmptyRgn			
				DC.W		$A8DD
				ENDM
				MACRO		_SetRecRgn				
				DC.W		$A8DE
				ENDM
				MACRO		_RectRgn				
				DC.W		$A8DF
				ENDM
				MACRO		_OfSetRgn				
				DC.W		$A8E0
				ENDM
				MACRO		_InSetRgn				
				DC.W		$A8E1
				ENDM
				MACRO		_EmptyRgn				
				DC.W		$A8E2
				ENDM
				MACRO		_EqualRgn				
				DC.W		$A8E3
				ENDM
				MACRO		_SectRgn				
				DC.W		$A8E4
				ENDM
				MACRO		_UnionRgn				
				DC.W		$A8E5
				ENDM
				MACRO		_DiffRgn				
				DC.W		$A8E6
				ENDM
				MACRO		_XOrRgn 				
				DC.W		$A8E7
				ENDM
				MACRO		_PtInRgn				
				DC.W		$A8E8
				ENDM
				MACRO		_RectInRgn				
				DC.W		$A8E9
				ENDM
				MACRO		_SetStdProcs			
				DC.W		$A8EA
				ENDM
				MACRO		_StdBits				
				DC.W		$A8EB
				ENDM
				MACRO		_CopyBits				
				DC.W		$A8EC
				ENDM
				MACRO		_StdTxMeas				
				DC.W		$A8ED
				ENDM
				MACRO		_StdGetPic				
				DC.W		$A8EE
				ENDM
				MACRO		_ScrollRect 			
				DC.W		$A8EF
				ENDM
				MACRO		_StdPutPic				
				DC.W		$A8F0
				ENDM
				MACRO		_StdComment 			
				DC.W		$A8F1
				ENDM
				MACRO		_PicComment 			
				DC.W		$A8F2
				ENDM
				MACRO		_OpenPicture			
				DC.W		$A8F3
				ENDM
				MACRO		_ClosePicture			
				DC.W		$A8F4
				ENDM
				MACRO		_KillPicture			
				DC.W		$A8F5
				ENDM
				MACRO		_DrawPicture			
				DC.W		$A8F6
				ENDM
				MACRO		_ScalePt				
				DC.W		$A8F8
				ENDM
				MACRO		_MapPt					
				DC.W		$A8F9
				ENDM
				MACRO		_MapRect				
				DC.W		$A8FA
				ENDM
				MACRO		_MapRgn 				
				DC.W		$A8FB
				ENDM
				MACRO		_MapPoly				
				DC.W		$A8FC
				ENDM
;end of QuickDraw Traps
; Tool Box Traps
				MACRO		_Count1Resources  		
				DC.W		$A80D
				ENDM
				MACRO		_Get1IxResource   		
				DC.W		$A80E
				ENDM
				MACRO		_Get1IxType 			
				DC.W		$A80F
				ENDM
				MACRO		_Unique1ID				
				DC.W		$A810
				ENDM
				MACRO		_TESelView				
				DC.W		$A811
				ENDM
				MACRO		_TEPinScroll			
				DC.W		$A812
				ENDM
				MACRO		_TEAutoView 			
				DC.W		$A813
				ENDM
				MACRO		_Pack8					
				DC.W		$A816
				ENDM
				MACRO		_FixATan2				
				DC.W		$A818
				ENDM
				MACRO		_XMunger				
				DC.W		$A819
				ENDM
				MACRO		_HOpenResFile			
				DC.W		$A81A
				ENDM
				MACRO		_HCreateResFile   		
				DC.W		$A81B
				ENDM
				MACRO		_Count1Types			
				DC.W		$A81C
				ENDM
				MACRO		_Get1Resource			
				DC.W		$A81F
				ENDM
				MACRO		_Get1NamedResource 		
				DC.W		$A820
				ENDM
				MACRO		_MaxSizeRsrc			
				DC.W		$A821
				ENDM
				MACRO		_InsMenuItem			
				DC.W		$A826
				ENDM
				MACRO		_HideDItem				
				DC.W		$A827
				ENDM
				MACRO		_ShowDItem				
				DC.W		$A828
				ENDM
				MACRO		_Pack9					
				DC.W		$A82B
				ENDM
				MACRO		_Pack10 				
				DC.W		$A82C
				ENDM
				MACRO		_Pack11 				
				DC.W		$A82D
				ENDM
				MACRO		_Pack12 				
				DC.W		$A82E
				ENDM
				MACRO		_Pack13 				
				DC.W		$A82F
				ENDM
				MACRO		_Pack14 				
				DC.W		$A830
				ENDM
				MACRO		_Pack15 				
				DC.W		$A831
				ENDM
				MACRO		_ScrnBitMap 			
				DC.W		$A833
				ENDM
				MACRO		_SetFScaleDisable 		
				DC.W		$A834
				ENDM
				MACRO		_FontMetrics			
				DC.W		$A835
				ENDM
				MACRO		_ZoomWindow 			
				DC.W		$A83A
				ENDM
				MACRO		_TrackBox				
				DC.W		$A83B
				ENDM
				MACRO		_InitFonts				
				DC.W		$A8FE
				ENDM
				MACRO		_GetFName				
				DC.W		$A8FF
				ENDM
				MACRO		_GetFNum				
				DC.W		$A900
				ENDM
				MACRO		_FMSwapFont 			
				DC.W		$A901
				ENDM
				MACRO		_RealFont				
				DC.W		$A902
				ENDM
				MACRO		_SetFontLock			
				DC.W		$A903
				ENDM
				MACRO		_DrawGrowIcon			
				DC.W		$A904
				ENDM
				MACRO		_DragGrayRgn			
				DC.W		$A905
				ENDM
				MACRO		_NewString				
				DC.W		$A906
				ENDM
				MACRO		_SetString				
				DC.W		$A907
				ENDM
				MACRO		_ShowHide				
				DC.W		$A908
				ENDM
				MACRO		_CalcVis				
				DC.W		$A909
				ENDM
				MACRO		_CalcVBehind			
				DC.W		$A90A
				ENDM
				MACRO		_ClipAbove				
				DC.W		$A90B
				ENDM
				MACRO		_PaintOne				
				DC.W		$A90C
				ENDM
				MACRO		_PaintBehind			
				DC.W		$A90D
				ENDM
				MACRO		_SaveOld				
				DC.W		$A90E
				ENDM
				MACRO		_DrawNew				
				DC.W		$A90F
				ENDM
				MACRO		_GetWMgrPort			
				DC.W		$A910
				ENDM
				MACRO		_CheckUpDate			
				DC.W		$A911
				ENDM
				MACRO		_InitWindows			
				DC.W		$A912
				ENDM
				MACRO		_NewWindow				
				DC.W		$A913
				ENDM
				MACRO		_DisposWindow			
				DC.W		$A914
				ENDM
				MACRO		_ShowWindow 			
				DC.W		$A915
				ENDM
				MACRO		_HideWindow 			
				DC.W		$A916
				ENDM
				MACRO		_GetWRefCon 			
				DC.W		$A917
				ENDM
				MACRO		_SetWRefCon 			
				DC.W		$A918
				ENDM
				MACRO		_GetWTitle				
				DC.W		$A919
				ENDM
				MACRO		_SetWTitle				
				DC.W		$A91A
				ENDM
				MACRO		_MoveWindow 			
				DC.W		$A91B
				ENDM
				MACRO		_HiliteWindow			
				DC.W		$A91C
				ENDM
				MACRO		_SizeWindow 			
				DC.W		$A91D
				ENDM
				MACRO		_TrackGoAway			
				DC.W		$A91E
				ENDM
				MACRO		_SelectWindow			
				DC.W		$A91F
				ENDM
				MACRO		_BringToFront			
				DC.W		$A920
				ENDM
				MACRO		_SendBehind 			
				DC.W		$A921
				ENDM
				MACRO		_BeginUpDate			
				DC.W		$A922
				ENDM
				MACRO		_EndUpDate				
				DC.W		$A923
				ENDM
				MACRO		_FrontWindow			
				DC.W		$A924
				ENDM
				MACRO		_DragWindow 			
				DC.W		$A925
				ENDM
				MACRO		_DragTheRgn 			
				DC.W		$A926
				ENDM
				MACRO		_InvalRgn				
				DC.W		$A927
				ENDM
				MACRO		_InvalRect				
				DC.W		$A928
				ENDM
				MACRO		_ValidRgn				
				DC.W		$A929
				ENDM
				MACRO		_ValidRect				
				DC.W		$A92A
				ENDM
				MACRO		_GrowWindow 			
				DC.W		$A92B
				ENDM
				MACRO		_FindWindow 			
				DC.W		$A92C
				ENDM
				MACRO		_CloseWindow			
				DC.W		$A92D
				ENDM
				MACRO		_SetWindowPic			
				DC.W		$A92E
				ENDM
				MACRO		_GetWindowPic			
				DC.W		$A92F
				ENDM
				MACRO		_InitMenus				
				DC.W		$A930
				ENDM
				MACRO		_NewMenu				
				DC.W		$A931
				ENDM
				MACRO		_DisposMenu 			
				DC.W		$A932
				ENDM
				MACRO		_AppendMenu 			
				DC.W		$A933
				ENDM
				MACRO		_ClearMenuBar			
				DC.W		$A934
				ENDM
				MACRO		_InsertMenu 			
				DC.W		$A935
				ENDM
				MACRO		_DeleteMenu 			
				DC.W		$A936
				ENDM
				MACRO		_DrawMenuBar			
				DC.W		$A937
				ENDM
				MACRO		_HiliteMenu 			
				DC.W		$A938
				ENDM
				MACRO		_EnableItem 			
				DC.W		$A939
				ENDM
				MACRO		_DisableItem			
				DC.W		$A93A
				ENDM
				MACRO		_GetMenuBar 			
				DC.W		$A93B
				ENDM
				MACRO		_SetMenuBar 			
				DC.W		$A93C
				ENDM
				MACRO		_MenuSelect 			
				DC.W		$A93D
				ENDM
				MACRO		_MenuKey				
				DC.W		$A93E
				ENDM
				MACRO		_GetItmIcon 			
				DC.W		$A93F
				ENDM
				MACRO		_SetItmIcon 			
				DC.W		$A940
				ENDM
				MACRO		_GetItmStyle			
				DC.W		$A941
				ENDM
				MACRO		_SetItmStyle			
				DC.W		$A942
				ENDM
				MACRO		_GetItmMark 			
				DC.W		$A943
				ENDM
				MACRO		_SetItmMark 			
				DC.W		$A944
				ENDM
				MACRO		_CheckItem				
				DC.W		$A945
				ENDM
				MACRO		_GetItem				
				DC.W		$A946
				ENDM
				MACRO		_SetItem				
				DC.W		$A947
				ENDM
				MACRO		_CalcMenuSize			
				DC.W		$A948
				ENDM
				MACRO		_GetMHandle 			
				DC.W		$A949
				ENDM
				MACRO		_SetMFlash				
				DC.W		$A94A
				ENDM
				MACRO		_PlotIcon				
				DC.W		$A94B
				ENDM
				MACRO		_FlashMenuBar			
				DC.W		$A94C
				ENDM
				MACRO		_AddResMenu 			
				DC.W		$A94D
				ENDM
				MACRO		_PinRect				
				DC.W		$A94E
				ENDM
				MACRO		_DeltaPoint 			
				DC.W		$A94F
				ENDM
				MACRO		_CountMItems			
				DC.W		$A950
				ENDM
				MACRO		_InsertResMenu			
				DC.W		$A951
				ENDM
				MACRO		_DelMenuItem			
				DC.W		$A952
				ENDM
				MACRO		_UpdtControl			
				DC.W		$A953
				ENDM
				MACRO		_NewControl 			
				DC.W		$A954
				ENDM
				MACRO		_DisposControl			
				DC.W		$A955
				ENDM
				MACRO		_KillControls			
				DC.W		$A956
				ENDM
				MACRO		_ShowControl			
				DC.W		$A957
				ENDM
				MACRO		_HideControl			
				DC.W		$A958
				ENDM
				MACRO		_MoveControl			
				DC.W		$A959
				ENDM
				MACRO		_GetCRefCon 			
				DC.W		$A95A
				ENDM
				MACRO		_SetCRefCon 			
				DC.W		$A95B
				ENDM
				MACRO		_SizeControl			
				DC.W		$A95C
				ENDM
				MACRO		_HiliteControl			
				DC.W		$A95D
				ENDM
				MACRO		_GetCTitle				
				DC.W		$A95E
				ENDM
				MACRO		_SetCTitle				
				DC.W		$A95F
				ENDM
				MACRO		_GetCtlValue			
				DC.W		$A960
				ENDM
				MACRO		_GetMinCtl				
				DC.W		$A961
				ENDM
				MACRO		_GetMaxCtl				
				DC.W		$A962
				ENDM
				MACRO		_SetCtlValue			
				DC.W		$A963
				ENDM
				MACRO		_SetMinCtl				
				DC.W		$A964
				ENDM
				MACRO		_SetMaxCtl				
				DC.W		$A965
				ENDM
				MACRO		_TestControl			
				DC.W		$A966
				ENDM
				MACRO		_DragControl			
				DC.W		$A967
				ENDM
				MACRO		_TrackControl			
				DC.W		$A968
				ENDM
				MACRO		_DrawControls			
				DC.W		$A969
				ENDM
				MACRO		_GetCtlAction			
				DC.W		$A96A
				ENDM
				MACRO		_SetCtlAction			
				DC.W		$A96B
				ENDM
				MACRO		_FindControl			
				DC.W		$A96C
				ENDM
				MACRO		_Draw1Control			
				DC.W		$A96D
				ENDM
				MACRO		_DeQueue				
				DC.W		$A96E
				ENDM
				MACRO		_EnQueue				
				DC.W		$A96F
				ENDM
				MACRO		_WaitNextEvent			
				DC.W		$A860
				ENDM
				MACRO		_GetNextEvent			
				DC.W		$A970
				ENDM
				MACRO		_EventAvail 			
				DC.W		$A971
				ENDM
				MACRO		_GetMouse				
				DC.W		$A972
				ENDM
				MACRO		_StillDown				
				DC.W		$A973
				ENDM
				MACRO		_Button 				
				DC.W		$A974
				ENDM
				MACRO		_TickCount				
				DC.W		$A975
				ENDM
				MACRO		_GetKeys				
				DC.W		$A976
				ENDM
				MACRO		_WaitMouseUp			
				DC.W		$A977
				ENDM
				MACRO		_UpdtDialog 			
				DC.W		$A978
				ENDM
				MACRO		_CouldDialog			
				DC.W		$A979
				ENDM
				MACRO		_FreeDialog 			
				DC.W		$A97A
				ENDM
				MACRO		_InitDialogs			
				DC.W		$A97B
				ENDM
				MACRO		_GetNewDialog			
				DC.W		$A97C
				ENDM
				MACRO		_NewDialog				
				DC.W		$A97D
				ENDM
				MACRO		_SelIText				
				DC.W		$A97E
				ENDM
				MACRO		_IsDialogEvent			
				DC.W		$A97F
				ENDM
				MACRO		_DialogSelect			
				DC.W		$A980
				ENDM
				MACRO		_DrawDialog 			
				DC.W		$A981
				ENDM
				MACRO		_CloseDialog			
				DC.W		$A982
				ENDM
				MACRO		_DisposDialog			
				DC.W		$A983
				ENDM
				MACRO		_FindDItem				
				DC.W		$A984
				ENDM
				MACRO		_Alert					
				DC.W		$A985
				ENDM
				MACRO		_StopAlert				
				DC.W		$A986
				ENDM
				MACRO		_NoteAlert				
				DC.W		$A987
				ENDM
				MACRO		_CautionAlert			
				DC.W		$A988
				ENDM
				MACRO		_CouldAlert 			
				DC.W		$A989
				ENDM
				MACRO		_FreeAlert				
				DC.W		$A98A
				ENDM
				MACRO		_ParamText				
				DC.W		$A98B
				ENDM
				MACRO		_ErrorSound 			
				DC.W		$A98C
				ENDM
				MACRO		_GetDItem				
				DC.W		$A98D
				ENDM
				MACRO		_SetDItem				
				DC.W		$A98E
				ENDM
				MACRO		_SetIText				
				DC.W		$A98F
				ENDM
				MACRO		_GetIText				
				DC.W		$A990
				ENDM
				MACRO		_ModalDialog			
				DC.W		$A991
				ENDM
				MACRO		_DetachResource   		
				DC.W		$A992
				ENDM
				MACRO		_SetResPurge			
				DC.W		$A993
				ENDM
				MACRO		_CurResFile 			
				DC.W		$A994
				ENDM
				MACRO		_InitResources			
				DC.W		$A995
				ENDM
				MACRO		_RsrcZoneInit			
				DC.W		$A996
				ENDM
				MACRO		_OpenResFile			
				DC.W		$A997
				ENDM
				MACRO		_UseResFile 			
				DC.W		$A998
				ENDM
				MACRO		_UpdateResFile			
				DC.W		$A999
				ENDM
				MACRO		_CloseResFile			
				DC.W		$A99A
				ENDM
				MACRO		_SetResLoad 			
				DC.W		$A99B
				ENDM
				MACRO		_CountResources   		
				DC.W		$A99C
				ENDM
				MACRO		_GetIndResource   		
				DC.W		$A99D
				ENDM
				MACRO		_CountTypes 			
				DC.W		$A99E
				ENDM
				MACRO		_GetIndType 			
				DC.W		$A99F
				ENDM
				MACRO		_GetResource			
				DC.W		$A9A0
				ENDM
				MACRO		_GetNamedResource 		
				DC.W		$A9A1
				ENDM
				MACRO		_LoadResource			
				DC.W		$A9A2
				ENDM
				MACRO		_ReleaseResource  		
				DC.W		$A9A3
				ENDM
				MACRO		_HomeResFile			
				DC.W		$A9A4
				ENDM
				MACRO		_SizeRsrc				
				DC.W		$A9A5
				ENDM
				MACRO		_GetResAttrs			
				DC.W		$A9A6
				ENDM
				MACRO		_SetResAttrs			
				DC.W		$A9A7
				ENDM
				MACRO		_GetResInfo 			
				DC.W		$A9A8
				ENDM
				MACRO		_SetResInfo 			
				DC.W		$A9A9
				ENDM
				MACRO		_ChangedResource  		
				DC.W		$A9AA
				ENDM
				MACRO		_AddResource			
				DC.W		$A9AB
				ENDM
				MACRO		_AddReference			
				DC.W		$A9AC
				ENDM
				MACRO		_RmveResource			
				DC.W		$A9AD
				ENDM
				MACRO		_RmveReference			
				DC.W		$A9AE
				ENDM
				MACRO		_ResError				
				DC.W		$A9AF
				ENDM
				MACRO		_WriteResource			
				DC.W		$A9B0
				ENDM
				MACRO		_CreateResFile			
				DC.W		$A9B1
				ENDM
				MACRO		_SystemEvent			
				DC.W		$A9B2
				ENDM
				MACRO		_SystemClick			
				DC.W		$A9B3
				ENDM
				MACRO		_SystemTask 			
				DC.W		$A9B4
				ENDM
				MACRO		_SystemMenu 			
				DC.W		$A9B5
				ENDM
				MACRO		_OpenDeskAcc			
				DC.W		$A9B6
				ENDM
				MACRO		_CloseDeskAcc			
				DC.W		$A9B7
				ENDM
				MACRO		_GetPattern 			
				DC.W		$A9B8
				ENDM
				MACRO		_GetCursor				
				DC.W		$A9B9
				ENDM
				MACRO		_GetString				
				DC.W		$A9BA
				ENDM
				MACRO		_GetIcon				
				DC.W		$A9BB
				ENDM
				MACRO		_GetPicture 			
				DC.W		$A9BC
				ENDM
				MACRO		_GetNewWindow			
				DC.W		$A9BD
				ENDM
				MACRO		_GetNewControl			
				DC.W		$A9BE
				ENDM
				MACRO		_GetRMenu				
				DC.W		$A9BF
				ENDM
				MACRO		_GetNewMBar 			
				DC.W		$A9C0
				ENDM
				MACRO		_UniqueID				
				DC.W		$A9C1
				ENDM
				MACRO		_SysEdit				
				DC.W		$A9C2
				ENDM
				MACRO		_OpenRFPerm 			
				DC.W		$A9C4
				ENDM
				MACRO		_RsrcMapEntry			
				DC.W		$A9C5
				ENDM
				MACRO		_Secs2Date				
				DC.W		$A9C6
				ENDM
				MACRO		_Date2Secs				
				DC.W		$A9C7
				ENDM
				MACRO		_SysBeep				
				DC.W		$A9C8
				ENDM
				MACRO		_SysError				
				DC.W		$A9C9
				ENDM
				MACRO		_TEGetText				
				DC.W		$A9CB
				ENDM
				MACRO		_TEInit 				
				DC.W		$A9CC
				ENDM
				MACRO		_TEDispose				
				DC.W		$A9CD
				ENDM
				MACRO		_TextBox				
				DC.W		$A9CE
				ENDM
				MACRO		_TESetText				
				DC.W		$A9CF
				ENDM
				MACRO		_TECalText				
				DC.W		$A9D0
				ENDM
				MACRO		_TESetSelect			
				DC.W		$A9D1
				ENDM
				MACRO		_TENew					
				DC.W		$A9D2
				ENDM
				MACRO		_TEUpdate				
				DC.W		$A9D3
				ENDM
				MACRO		_TEClick				
				DC.W		$A9D4
				ENDM
				MACRO		_TECopy 				
				DC.W		$A9D5
				ENDM
				MACRO		_TECut					
				DC.W		$A9D6
				ENDM
				MACRO		_TEDelete				
				DC.W		$A9D7
				ENDM
				MACRO		_TEActivate 			
				DC.W		$A9D8
				ENDM
				MACRO		_TEDeactivate			
				DC.W		$A9D9
				ENDM
				MACRO		_TEIdle 				
				DC.W		$A9DA
				ENDM
				MACRO		_TEPaste				
				DC.W		$A9DB
				ENDM
				MACRO		_TEKey					
				DC.W		$A9DC
				ENDM
				MACRO		_TEScroll				
				DC.W		$A9DD
				ENDM
				MACRO		_TEInsert				
				DC.W		$A9DE
				ENDM
				MACRO		_TESetJust				
				DC.W		$A9DF
				ENDM
				MACRO		_Munger 				
				DC.W		$A9E0
				ENDM
				MACRO		_HandToHand 			
				DC.W		$A9E1
				ENDM
				MACRO		_PtrToXHand 			
				DC.W		$A9E2
				ENDM
				MACRO		_PtrToHand				
				DC.W		$A9E3
				ENDM
				MACRO		_HandAndHand			
				DC.W		$A9E4
				ENDM
				MACRO		_InitPack				
				DC.W		$A9E5
				ENDM
				MACRO		_InitAllPacks			
				DC.W		$A9E6
				ENDM
				MACRO		_Pack0					
				DC.W		$A9E7
				ENDM
				MACRO		_Pack1					
				DC.W		$A9E8
				ENDM
				MACRO		_Pack2					
				DC.W		$A9E9
				ENDM
				MACRO		_Pack3					
				DC.W		$A9EA
				ENDM
				MACRO		_FP68K					
				DC.W		$A9EB
				ENDM
				MACRO		_Pack4					
				DC.W		$A9EB
				ENDM
				MACRO		_Elems68K				
				DC.W		$A9EC
				ENDM
				MACRO		_Pack5					
				DC.W		$A9EC
				ENDM
				MACRO		_Pack6					
				DC.W		$A9ED
				ENDM
				MACRO		_DECSTR68K				
				DC.W		$A9EE
				ENDM
				MACRO		_Pack7					
				DC.W		$A9EE
				ENDM
				MACRO		_PtrAndHand 			
				DC.W		$A9EF
				ENDM
				MACRO		_LoadSeg				
				DC.W		$A9F0
				ENDM
				MACRO		_UnLoadSeg				
				DC.W		$A9F1
				ENDM
				MACRO		_Launch 				
				DC.W		$A9F2
				ENDM
				MACRO		_Chain					
				DC.W		$A9F3
				ENDM
				MACRO		_ExitToShell			
				DC.W		$A9F4
				ENDM
				MACRO		_GetAppParms			
				DC.W		$A9F5
				ENDM
				MACRO		_GetResFileAttrs  		
				DC.W		$A9F6
				ENDM
				MACRO		_SetResFileAttrs  		
				DC.W		$A9F7
				ENDM
				MACRO		_MethodDispatch   		
				DC.W		$A9F8
				ENDM
				MACRO		_InfoScrap				
				DC.W		$A9F9
				ENDM
				MACRO		_UnlodeScrap			
				DC.W		$A9FA
				ENDM
				MACRO		_UnloadScrap			
				DC.W		$A9FA
				ENDM
				MACRO		_LodeScrap				
				DC.W		$A9FB
				ENDM
				MACRO		_LoadScrap				
				DC.W		$A9FB
				ENDM
				MACRO		_ZeroScrap				
				DC.W		$A9FC
				ENDM
				MACRO		_GetScrap				
				DC.W		$A9FD
				ENDM
				MACRO		_PutScrap				
				DC.W		$A9FE
				ENDM
				MACRO		_Debugger				
				DC.W		$A9FF
				ENDM
				MACRO		_DebugStr				
				DC.W		$ABFF
				ENDM
; end of Tool Box Traps
; System Traps
;_______________________________________________________________________
;
; Core routine system TRAPS
;
;_______________________________________________________________________
; First we have the I/O core routines. These are also used by
; the file system.
				MACRO		_Open					
				DC.W		$A000
				ENDM
				MACRO		_Close					
				DC.W		$A001
				ENDM
				MACRO		_Read					
				DC.W		$A002
				ENDM
				MACRO		_Write					
				DC.W		$A003
				ENDM
				MACRO		_Control				
				DC.W		$A004
				ENDM
				MACRO		_Status 				
				DC.W		$A005
				ENDM
				MACRO		_KillIO 				
				DC.W		$A006
				ENDM
				MACRO		_GetVolInfo 			
				DC.W		$A007
				ENDM
				MACRO		_Create 				
				DC.W		$A008
				ENDM
				MACRO		_Delete 				
				DC.W		$A009
				ENDM
				MACRO		_OpenRF 				
				DC.W		$A00A
				ENDM
				MACRO		_ReName 				
				DC.W		$A00B
				ENDM
				MACRO		_GetFileInfo			
				DC.W		$A00C
				ENDM
				MACRO		_SetFileInfo			
				DC.W		$A00D
				ENDM
				MACRO		_UnMountVol 			
				DC.W		$A00E
				ENDM
				MACRO		_MountVol				
				DC.W		$A00F
				ENDM
				MACRO		_Allocate				
				DC.W		$A010
				ENDM
				MACRO		_GetEOF 				
				DC.W		$A011
				ENDM
				MACRO		_SetEOF 				
				DC.W		$A012
				ENDM
				MACRO		_FlushVol				
				DC.W		$A013
				ENDM
				MACRO		_GetVol 				
				DC.W		$A014
				ENDM
				MACRO		_SetVol 				
				DC.W		$A015
				ENDM
				MACRO		_FInitQueue 			
				DC.W		$A016
				ENDM
				MACRO		_Eject					
				DC.W		$A017
				ENDM
				MACRO		_GetFPos				
				DC.W		$A018
				ENDM
;These are the HFS additions
				MACRO	_TFSCORE
				IF			%1 <> ''
				LEA 		%1,A0
				ENDIF
				IF			%3 = ''
				DC.W		$A200+%2
				ENDIF
				IF			%3 = 'REGS'
				DC.W		$A300+%2
				ENDIF
				IF			%3 = 'ASYNC'
				DC.W		$A600+%2
				ENDIF
				IF			%3 = 'SYS'
				DC.W		$A600+%2
				ENDIF
				IF			%3 = 'IMMED'
				DC.W		$A200+%2
				ENDIF
				ENDM
				MACRO	_FSControl
				MOVEQ		#0,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_OpenWD
				MOVEQ		#1,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_CloseWD
				MOVEQ		#2,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO		_HSetVol				
				DC.W		$A215
				ENDM
				MACRO		_HGetVol				
				DC.W		$A214
				ENDM
				MACRO	_CatMove
				MOVEQ		#5,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_DirCreate
				MOVEQ		#6,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_GetWDInfo
				MOVEQ		#7,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_GetFCBInfo
				MOVEQ		#8,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_GetCatInfo
				MOVEQ		#9,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_SetCatInfo
				MOVEQ		#10,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_SetVolInfo
				MOVEQ		#11,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_SetPMSP
				MOVEQ		#12,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_LockRng
				MOVEQ		#16,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_UnlockRng
				MOVEQ		#17,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_GetVolParms
				MOVEQ		#$30,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_GetLogInInfo
				MOVEQ		#$31,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_GetDirAccess
				MOVEQ		#$32,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_SetDirAccess
				MOVEQ		#$33,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_MapID
				MOVEQ		#$34,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_MapName
				MOVEQ		#$35,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_CopyFile
				MOVEQ		#$36,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_MoveRename
				MOVEQ		#$37,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_OpenDeny
				MOVEQ		#$38,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO	_OpenRFDeny
				MOVEQ		#$39,D0
				_TFSCore	%1,96,%2
				ENDM
				MACRO		_HOpen					
				DC.W		$A200
				ENDM
				MACRO		_HGetVInfo				
				DC.W		$A207
				ENDM
				MACRO		_HCreate				
				DC.W		$A208
				ENDM
				MACRO		_HDelete				
				DC.W		$A209
				ENDM
				MACRO		_HOpenRF				
				DC.W		$A20A
				ENDM
				MACRO		_HRename				
				DC.W		$A20B
				ENDM
				MACRO		_HGetFileInfo			
				DC.W		$A20C
				ENDM
				MACRO		_HSetFileInfo			
				DC.W		$A20D
				ENDM
				MACRO		_AllocContig			
				DC.W		$A210
				ENDM
;				MACRO		_SetPEOF 		
;				DC.W		$A200+18
;				ENDM
				MACRO		_HSetFLock				
				DC.W		$A241
				ENDM
				MACRO		_HRstFLock				
				DC.W		$A242
				ENDM
; end of HFS additions
; Here are the memory manager core routines
				MACRO		_InitZone				
				DC.W		$A019
				ENDM
				MACRO		_GetZone				
				DC.W		$A11A
				ENDM
				MACRO		_SetZone				
				DC.W		$A01B
				ENDM
				MACRO		_FreeMem				
				DC.W		$A01C
				ENDM
				MACRO		_MaxMem 				
				DC.W		$A11D
				ENDM
				MACRO		_NewPtr 				
				DC.W		$A11E
				ENDM
				MACRO		_DisposPtr				
				DC.W		$A01F
				ENDM
				MACRO		_SetPtrSize 			
				DC.W		$A020
				ENDM
				MACRO		_GetPtrSize 			
				DC.W		$A021
				ENDM
				MACRO		_NewHandle				
				DC.W		$A122
				ENDM
				MACRO		_DisposHandle			
				DC.W		$A023
				ENDM
				MACRO		_SetHandleSize			
				DC.W		$A024
				ENDM
				MACRO		_GetHandleSize			
				DC.W		$A025
				ENDM
				MACRO		_HandleZone 			
				DC.W		$A126
				ENDM
				MACRO		_ReAllocHandle			
				DC.W		$A027
				ENDM
				MACRO		_RecoverHandle			
				DC.W		$A128
				ENDM
				MACRO		_HLock					
				DC.W		$A029
				ENDM
				MACRO		_HUnlock				
				DC.W		$A02A
				ENDM
				MACRO		_EmptyHandle			
				DC.W		$A02B
				ENDM
				MACRO		_InitApplZone			
				DC.W		$A02C
				ENDM
				MACRO		_SetApplLimit			
				DC.W		$A02D
				ENDM
				MACRO		_BlockMove				
				DC.W		$A02E
				ENDM
; Here are the event manager routines
				MACRO		_PostEvent				
				DC.W		$A02F
				ENDM
				MACRO		_PPostEvent 			
				DC.W		$A12F					;preserves A0 on return
				ENDM
				MACRO		_OSEventAvail			
				DC.W		$A030
				ENDM
				MACRO		_GetOSEvent 			
				DC.W		$A031
				ENDM
				MACRO		_FlushEvents			
				DC.W		$A032
				ENDM
; Here are the utility core routines
				MACRO		_VInstall				
				DC.W		$A033
				ENDM
				MACRO		_VRemove				
				DC.W		$A034
				ENDM
				MACRO		_OffLine				
				DC.W		$A035
				ENDM
				MACRO		_MoreMasters			
				DC.W		$A036
				ENDM
				MACRO		_WriteParam 			
				DC.W		$A038
				ENDM
				MACRO		_ReadDateTime			
				DC.W		$A039
				ENDM
				MACRO		_SetDateTime			
				DC.W		$A03A
				ENDM
				MACRO		_Delay					
				DC.W		$A03B
				ENDM
				MACRO		_CmpString				
				DC.W		$A03C
				ENDM
				MACRO		_DrvrInstall			
				DC.W		$A03D
				ENDM
				MACRO		_DrvrRemove 			
				DC.W		$A03E
				ENDM
				MACRO		_InitUtil				
				DC.W		$A03F
				ENDM
				MACRO		_ResrvMem				
				DC.W		$A040
				ENDM
				MACRO		_SetFilLock 			
				DC.W		$A041
				ENDM
				MACRO		_RstFilLock 			
				DC.W		$A042
				ENDM
				MACRO		_SetFilType 			
				DC.W		$A043
				ENDM
				MACRO		_SetFPos				
				DC.W		$A044
				ENDM
				MACRO		_FlushFile				
				DC.W		$A045
				ENDM
				MACRO		_GetTrapAddress   		
				DC.W		$A146
				ENDM
				MACRO		_NGetTrapAddress   		
				DC.W		($A146|%1)
				ENDM
				MACRO		_SetTrapAddress   		
				DC.W		$A047
				ENDM
				MACRO		_NSetTrapAddress   		
				DC.W		($A047|%1)
				ENDM
				MACRO		_PtrZone				
				DC.W		$A148
				ENDM
				MACRO		_HPurge 				
				DC.W		$A049
				ENDM
				MACRO		_HNoPurge				
				DC.W		$A04A
				ENDM
				MACRO		_SetGrowZone			
				DC.W		$A04B
				ENDM
				MACRO		_CompactMem 			
				DC.W		$A04C
				ENDM
				MACRO		_PurgeMem				
				DC.W		$A04D
				ENDM
				MACRO		_AddDrive				
				DC.W		$A04E
				ENDM
				MACRO		_RDrvrInstall			
				DC.W		$A04F
				ENDM
				MACRO		_LwrString				
				DC.W		$A056
				ENDM
				MACRO		_UprString				
				DC.W		$A054
				ENDM
				MACRO		_SetApplBase			
				DC.W		$A057
				ENDM
				MACRO		_OSDispatch 			
				DC.W		$A88F					;MultiFinder trap
				ENDM
;Macros
				MACRO	_MFMaxMem
				MOVE.W		#21,-(SP)
				_OSDispatch
				ENDM
				MACRO	_MFFreeMem
				MOVE.W		#24,-(SP)
				_OSDispatch
				ENDM
				MACRO	_MFTempNewHandle
				MOVE.W		#29,-(SP)
				_OSDispatch
				ENDM
				MACRO	_MFTempHLock
				MOVE.W		#30,-(SP)
				_OSDispatch
				ENDM
				MACRO	_MFTempHUnlock
				MOVE.W		#31,-(SP)
				_OSDispatch
				ENDM
				MACRO	_MFTempDisposHandle
				MOVE.W		#32,-(SP)
				_OSDispatch
				ENDM
				MACRO		_RelString				
				DC.W		$A050
				ENDM
				MACRO		_ReadXPRam				
				DC.W		$A051
				ENDM
				MACRO		_WriteXPRam 			
				DC.W		$A052
				ENDM
				MACRO		_InsTime				
				DC.W		$A058
				ENDM
				MACRO		_RmvTime				
				DC.W		$A059
				ENDM
				MACRO		_PrimeTime				
				DC.W		$A05A
				ENDM
				MACRO		_MaxBlock				
				DC.W		$A061
				ENDM
				MACRO		_PurgeSpace 			
				DC.W		$A162
				ENDM
				MACRO		_MaxApplZone			
				DC.W		$A063
				ENDM
				MACRO		_MoveHHi				
				DC.W		$A064
				ENDM
				MACRO		_StackSpace 			
				DC.W		$A065
				ENDM
				MACRO		_NewEmptyHandle   		
				DC.W		$A166
				ENDM
				MACRO		_HSetRBit				
				DC.W		$A067
				ENDM
				MACRO		_HClrRBit				
				DC.W		$A068
				ENDM
				MACRO		_HGetState				
				DC.W		$A069
				ENDM
				MACRO		_HSetState				
				DC.W		$A06A
				ENDM
				MACRO		_InitFS 				
				DC.W		$A06C
				ENDM
				MACRO		_InitEvents 			
				DC.W		$A06D
				ENDM
				MACRO		_StripAddress			
				DC.W		$A055					; new memory manager trap
				ENDM
				MACRO		_SetAppBase 			
				DC.W		$A057
				ENDM
				MACRO		_SwapMMUMode			
				DC.W		$A05D
				ENDM
				MACRO		_SlotVInstall			
				DC.W		$A06F
				ENDM
				MACRO		_SlotVRemove			
				DC.W		$A070
				ENDM
				MACRO		_AttachVBL				
				DC.W		$A071
				ENDM
				MACRO		_DoVBLTask				
				DC.W		$A072
				ENDM
				MACRO		_SIntInstall			
				DC.W		$A075
				ENDM
				MACRO		_SIntRemove 			
				DC.W		$A076
				ENDM
				MACRO		_CountADBs				
				DC.W		$A077
				ENDM
				MACRO		_GetIndADB				
				DC.W		$A078
				ENDM
				MACRO		_GetADBInfo 			
				DC.W		$A079
				ENDM
				MACRO		_SetADBInfo 			
				DC.W		$A07A
				ENDM
				MACRO		_ADBReInit				
				DC.W		$A07B
				ENDM
				MACRO		_ADBOp					
				DC.W		$A07C
				ENDM
				MACRO		_GetDefaultStartup 		
				DC.W		$A07D
				ENDM
				MACRO		_SetDefaultStartup 		
				DC.W		$A07E
				ENDM
				MACRO		_InternalWait			
				DC.W		$A07F
				ENDM
				MACRO		_RGetResource			
				DC.W		$A80C
				ENDM
				MACRO		_GetVideoDefault  		
				DC.W		$A080
				ENDM
				MACRO		_SetVideoDefault  		
				DC.W		$A081
				ENDM
				MACRO		_DTInstall				
				DC.W		$A082
				ENDM
				MACRO		_SetOSDefault			
				DC.W		$A083
				ENDM
				MACRO		_GetOSDefault			
				DC.W		$A084
				ENDM
				MACRO		_Sleep					
				DC.W		$A08A
				ENDM
				MACRO		_SysEnvirons			
				DC.W		$A090
				ENDM
				MACRO		_InitProcMenu			
				DC.W		$A808
				ENDM
				MACRO		_GetItemCmd 			
				DC.W		$A84E
				ENDM
				MACRO		_SetItemCmd 			
				DC.W		$A84F
				ENDM
				MACRO		_PopUpMenuSelect  		
				DC.W		$A80B
				ENDM
				MACRO		_KeyTrans				
				DC.W		$A9C3
				ENDM
				MACRO	_GetTimeOut
				MOVEA.W 	#0,A0
				_InternalWait
				ENDM
				MACRO	_SetTimeOut
				MOVEA.W 	#1,A0
				_InternalWait
				ENDM
; TextEdit
				MACRO		_TEGetOffset			
				DC.W		$A83C
				ENDM
				MACRO		_TEDispatch 			
				DC.W		$A83D
				ENDM
				MACRO		_TEStyleNew 			
				DC.W		$A83E
				ENDM
; Color Quickdraw
				MACRO		_OpenCport				
				DC.W		$AA00
				ENDM
				MACRO		_InitCport				
				DC.W		$AA01
				ENDM
				MACRO		_CloseCPort 			
				DC.W		$A87D
				ENDM
				MACRO		_NewPixMap				
				DC.W		$AA03
				ENDM
				MACRO		_DisposPixMap			
				DC.W		$AA04
				ENDM
				MACRO		_CopyPixMap 			
				DC.W		$AA05
				ENDM
				MACRO		_SetPortPix 			
				DC.W		$AA06
				ENDM
				MACRO		_NewPixPat				
				DC.W		$AA07
				ENDM
				MACRO		_DisposPixPat			
				DC.W		$AA08
				ENDM
				MACRO		_CopyPixPat 			
				DC.W		$AA09
				ENDM
				MACRO		_PenPixPat				
				DC.W		$AA0A
				ENDM
				MACRO		_BackPixPat 			
				DC.W		$AA0B
				ENDM
				MACRO		_GetPixPat				
				DC.W		$AA0C
				ENDM
				MACRO		_MakeRGBPat 			
				DC.W		$AA0D
				ENDM
				MACRO		_FillCRect				
				DC.W		$AA0E
				ENDM
				MACRO		_FillCOval				
				DC.W		$AA0F
				ENDM
				MACRO		_FillCRoundRect   		
				DC.W		$AA10
				ENDM
				MACRO		_FillCArc				
				DC.W		$AA11
				ENDM
				MACRO		_FillCRgn				
				DC.W		$AA12
				ENDM
				MACRO		_FillCPoly				
				DC.W		$AA13
				ENDM
				MACRO		_RGBForeColor			
				DC.W		$AA14
				ENDM
				MACRO		_RGBBackColor			
				DC.W		$AA15
				ENDM
				MACRO		_SetCPixel				
				DC.W		$AA16
				ENDM
				MACRO		_GetCPixel				
				DC.W		$AA17
				ENDM
				MACRO		_GetCTable				
				DC.W		$AA18
				ENDM
				MACRO		_GetForeColor			
				DC.W		$AA19
				ENDM
				MACRO		_GetBackColor			
				DC.W		$AA1A
				ENDM
				MACRO		_GetCCursor 			
				DC.W		$AA1B
				ENDM
				MACRO		_SetCCursor 			
				DC.W		$AA1C
				ENDM
				MACRO		_AllocCursor			
				DC.W		$AA1D
				ENDM
				MACRO		_GetCIcon				
				DC.W		$AA1E
				ENDM
				MACRO		_PlotCIcon				
				DC.W		$AA1F
				ENDM
				MACRO		_OpColor				
				DC.W		$AA21
				ENDM
				MACRO		_HiliteColor			
				DC.W		$AA22
				ENDM
				MACRO		_CharExtra				
				DC.W		$AA23
				ENDM
				MACRO		_DisposCTable			
				DC.W		$AA24
				ENDM
				MACRO		_DisposCIcon			
				DC.W		$AA25
				ENDM
				MACRO		_DisposCCursor			
				DC.W		$AA26
				ENDM
				MACRO		_SeedCFill				
				DC.W		$AA50
				ENDM
				MACRO		_CalcCMask				
				DC.W		$AA4F
				ENDM
; Routines for video devices
				MACRO		_GetMaxDevice			
				DC.W		$AA27
				ENDM
				MACRO		_GetCTSeed				
				DC.W		$AA28
				ENDM
				MACRO		_GetDeviceList			
				DC.W		$AA29
				ENDM
				MACRO		_GetMainDevice			
				DC.W		$AA2A
				ENDM
				MACRO		_GetNextDevice			
				DC.W		$AA2B
				ENDM
				MACRO		_TestDeviceAttribute 		
				DC.W		$AA2C
				ENDM
				MACRO		_SetDeviceAttribute 		
				DC.W		$AA2D
				ENDM
				MACRO		_InitGDevice			
				DC.W		$AA2E
				ENDM
				MACRO		_NewGDevice 			
				DC.W		$AA2F
				ENDM
				MACRO		_DisposGDevice			
				DC.W		$AA30
				ENDM
				MACRO		_SetGDevice 			
				DC.W		$AA31
				ENDM
				MACRO		_GetGDevice 			
				DC.W		$AA32
				ENDM
; Color Manager
				MACRO		_Color2Index			
				DC.W		$AA33
				ENDM
				MACRO		_Index2Color			
				DC.W		$AA34
				ENDM
				MACRO		_InvertColor			
				DC.W		$AA35
				ENDM
				MACRO		_RealColor				
				DC.W		$AA36
				ENDM
				MACRO		_GetSubTable			
				DC.W		$AA37
				ENDM
				MACRO		_UpdatePixMap			
				DC.W		$AA38
				ENDM
; Dialog Manager
				MACRO		_NewCDialog 			
				DC.W		$AA4B
				ENDM
				MACRO		_MakeITable 			
				DC.W		$AA39
				ENDM
				MACRO		_AddSearch				
				DC.W		$AA3A
				ENDM
				MACRO		_AddComp				
				DC.W		$AA3B
				ENDM
				MACRO		_SetClientID			
				DC.W		$AA3C
				ENDM
				MACRO		_ProtectEntry			
				DC.W		$AA3D
				ENDM
				MACRO		_ReserveEntry			
				DC.W		$AA3E
				ENDM
				MACRO		_SetEntries 			
				DC.W		$AA3F
				ENDM
				MACRO		_QDError				
				DC.W		$AA40
				ENDM
				MACRO		_SaveEntries			
				DC.W		$AA49
				ENDM
				MACRO		_RestoreEntries   		
				DC.W		$AA4A
				ENDM
				MACRO		_DelSearch				
				DC.W		$AA4C
				ENDM
				MACRO		_DelComp				
				DC.W		$AA4D
				ENDM
				MACRO		_SetStdCProcs			
				DC.W		$AA4E
				ENDM
				MACRO		_StdOpcodeProc			
				DC.W		$ABF8
				ENDM
; Color ToolBox
				MACRO		_SetWinColor			
				DC.W		$AA41
				ENDM
				MACRO		_GetAuxWin				
				DC.W		$AA42
				ENDM
				MACRO		_SetCtlColor			
				DC.W		$AA43
				ENDM
				MACRO		_GetAuxCtl				
				DC.W		$AA44
				ENDM
				MACRO		_NewCWindow 			
				DC.W		$AA45
				ENDM
				MACRO		_GetNewCWindow			
				DC.W		$AA46
				ENDM
				MACRO		_SetDeskCPat			
				DC.W		$AA47
				ENDM
				MACRO		_GetCWMgrPort			
				DC.W		$AA48
				ENDM
				MACRO		_GetCVariant			
				DC.W		$A809
				ENDM
				MACRO		_GetWVariant			
				DC.W		$A80A
				ENDM
; color menus
				MACRO		_DelMCEntries			
				DC.W		$AA60
				ENDM
				MACRO		_GetMCInfo				
				DC.W		$AA61
				ENDM
				MACRO		_SetMCInfo				
				DC.W		$AA62
				ENDM
				MACRO		_DispMCInfo 			
				DC.W		$AA63
				ENDM
				MACRO		_GetMCEntry 			
				DC.W		$AA64
				ENDM
				MACRO		_SetMCEntries			
				DC.W		$AA65
				ENDM
; other menu stuff
				MACRO		_MenuChoice 			
				DC.W		$AA66
				ENDM
; Font Manager
				MACRO		_SetFractEnable   		
				DC.W		$A814
				ENDM
				MACRO		_PMgrOp 				
				DC.W		$A085
				ENDM
				MACRO		_HUnmountVol			
				DC.W		$A20E
				ENDM
; Palette Manager Traps
				MACRO		_InitPalettes			
				DC.W		$AA90
				ENDM
				MACRO		_NewPalette 			
				DC.W		$AA91
				ENDM
				MACRO		_GetNewPalette			
				DC.W		$AA92
				ENDM
				MACRO		_DisposePalette   		
				DC.W		$AA93
				ENDM
				MACRO		_ActivatePalette  		
				DC.W		$AA94
				ENDM
				MACRO		_SetPalette 			
				DC.W		$AA95
				ENDM
				MACRO		_GetPalette 			
				DC.W		$AA96
				ENDM
				MACRO		_PmForeColor			
				DC.W		$AA97
				ENDM
				MACRO		_PmBackColor			
				DC.W		$AA98
				ENDM
				MACRO		_AnimateEntry			
				DC.W		$AA99
				ENDM
				MACRO		_AnimatePalette   		
				DC.W		$AA9A
				ENDM
				MACRO		_GetEntryColor			
				DC.W		$AA9B
				ENDM
				MACRO		_SetEntryColor			
				DC.W		$AA9C
				ENDM
				MACRO		_GetEntryUsage			
				DC.W		$AA9D
				ENDM
				MACRO		_SetEntryUsage			
				DC.W		$AA9E
				ENDM
				MACRO		_CTab2Palette			
				DC.W		$AA9F
				ENDM
				MACRO		_Palette2CTab			
				DC.W		$AAA0
				ENDM
				MACRO		_CopyPalette			
				DC.W		$AAA1
				ENDM
; Sound Manager Traps
				MACRO		_SndDoCommand			
				DC.W		$A803
				ENDM
				MACRO		_SndDoImmediate   		
				DC.W		$A804
				ENDM
				MACRO		_SndAddModifier   		
				DC.W		$A802
				ENDM
				MACRO		_SndNewChannel			
				DC.W		$A807
				ENDM
				MACRO		_SndDisposeChannel 		
				DC.W		$A801
				ENDM
				MACRO		_SndPlay				
				DC.W		$A805
				ENDM
				MACRO		_SndControl 			
				DC.W		$A806
				ENDM
				MACRO		_PutIcon				
				DC.W		$A9CA
				ENDM
				MACRO		_SlotManager			
				DC.W		$A06E
				ENDM
				MACRO		_ScriptUtil 			
				DC.W		$A8B5
				ENDM
				MACRO		_SCSIDispatch			
				DC.W		$A815
				ENDM
				MACRO		_Long2Fix				
				DC.W		$A83F
				ENDM
				MACRO		_Fix2Long				
				DC.W		$A840
				ENDM
				MACRO		_Fix2Frac				
				DC.W		$A841
				ENDM
				MACRO		_Frac2Fix				
				DC.W		$A842
				ENDM
				MACRO		_Fix2X					
				DC.W		$A843
				ENDM
				MACRO		_X2Fix					
				DC.W		$A844
				ENDM
				MACRO		_Frac2X 				
				DC.W		$A845
				ENDM
				MACRO		_X2Frac 				
				DC.W		$A846
				ENDM
				MACRO		_NMInstall				
				DC.W		$A05E
				ENDM
				MACRO		_NMRemove				
				DC.W		$A05F
				ENDM
