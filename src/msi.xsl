<?xml version="1.0" encoding="UTF-8"?>
<!-- 
  $Log$
  Revision 1.1  2001/12/23 23:22:15  legalize
  Initial revision

  Revision 1.5  2001/05/08 15:08:19  dgehrige
  * Added cross-referencing hyperlinks.

  Revision 1.4  2001/05/07 15:15:47  dgehrige
  no message

  Revision 1.3  2001/05/07 15:12:38  dgehrige
  * Fixed comments (Dan Rolander <Dan.Rolander@marriott.com>)

  Revision 1.2  2001/05/07 15:06:48  dgehrige
  * Added summary information (Dan Rolander <Dan.Rolander@marriott.com>)
  
  Revision 1.1  2001/04/26 12:00:00  dgehrige
  * Initial revision
--> 
<!-- msi.xsl -->
<xsl:stylesheet 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:html="http://www.w3.org/1999/xhtml"
  xmlns:dt="urn:schemas-microsoft-com:datatypes">
<xsl:output method="html" />
<xsl:template match="/">
<html>
<head>
<script language="vbscript" type="text/vbscript">
<![CDATA[
<!--
Function WriteBinData(strMD5)
  WriteBinData = False
  Dim oNode
  Set oNode = document.XMLDocument.selectSingleNode("//td[@md5='" & strMD5 & "']")
  If oNode Is Nothing Then
    MsgBox "Unable to find binary data."
    Exit Function
  End If
  
  Dim strSaveTo
  If document.location.protocol = "file:" Then
    strSaveTo = document.location.pathname
    strSaveTo = Mid(strSaveTo, 2, InStrRev(strSaveTo, "\") - 1)
  End If
  strSaveTo = Inputbox("Save binary stream as:", "Save Binary File As", strSaveTo)
  
  If strSaveTo = "" Then
    Exit Function
  End If
    
  Dim arrBuffer
  arrBuffer = oNode.nodeTypedValue

  Dim sTemp
  nMax = Len(arrBuffer)
  With CreateObject("Scripting.FileSystemObject")
    With .CreateTextFile(strSaveTo, True, False)
      Do Until Len(arrBuffer) = 0
        window.status = "Percentage completed: " & CStr(CInt(100 - (100 * Len(arrBuffer) / nMax)))
        ReDim sOut(5000 - 1)
        sTemp = Left(arrBuffer, 5000)
        For j = 0 To 5000 - 1
          sOut(j) = Chr(AscB(LeftB(sTemp,1)))
          sTemp = MidB(sTemp,2)
          if sTemp = "" Then Exit For
        Next ' j
        .Write Join(sOut, "")
        arrBuffer = MidB(arrBuffer, 5000 + 1)
      Loop
    End With ' Output file
  End With ' FSO
  
  window.status = "Done."
End Function 

-->
]]>
</script>
</head>
<body>

<h1>Windows Installer Database</h1>
<p><address>Generated by msi2xml (c) 2001 <a href="mailto:gehriger@linkad.com">Daniel Gehriger</a></address></p>
<hr/>

<h2>Summary Information</h2>
  <table>
    <tr>
      <td><b>Title:</b></td>
      <td><xsl:value-of select="//summary/title"/></td>
    </tr>
    <tr>
      <td><b>Subject:</b></td>
      <td><xsl:value-of select="//summary/subject"/></td>
    </tr>
    <tr>
      <td><b>Author:</b></td>
      <td><xsl:value-of select="//summary/author"/></td>
    </tr>
    <tr>
      <td><b>Keywords:</b></td>
      <td><xsl:value-of select="//summary/keywords"/></td>
    </tr>
    <tr>
      <td><b>Comments:</b></td>
      <td><xsl:value-of select="//summary/comments"/></td>
    </tr>
    <tr>
      <td><b>Revision Number:</b></td>
      <td><xsl:value-of select="//summary/revnumber"/></td>
    </tr>
    <tr>
      <td><b>Last Saved By:</b></td>
      <td><xsl:value-of select="//summary/lastauthor"/></td>
    </tr>
    <tr>
      <td><b>Last Saved Date/Time:</b></td>
      <td><xsl:value-of select="//summary/lastsavedtm"/></td>
    </tr>
  </table>
<hr/>

<!-- TOC -->
<a name="___TOC___"/>
<h2>Table of Contents</h2>
<xsl:for-each select="msi/table">
  <a>
    <xsl:attribute name="href">
      #<xsl:value-of select="@name"/>
    </xsl:attribute>
    <xsl:value-of select="@name"/>
  </a>
    <xsl:text> | </xsl:text>
</xsl:for-each>
<hr/>

<!-- Tables -->
<xsl:for-each select="msi/table">
  <!-- table header -->
  <a>
    <xsl:attribute name="name">
      <xsl:value-of select="@name"/>
    </xsl:attribute>
  </a>
  <h2><xsl:value-of select="@name"/></h2>
  
  <!-- links -->
  <xsl:if test="./preceding-sibling::*[1]">
  <a>
    <xsl:attribute name="href">
      #<xsl:value-of select="preceding-sibling::*[1]/@name"/>
    </xsl:attribute>previous</a>
  <xsl:text> | </xsl:text>
  </xsl:if>
  
  <a href="#___TOC___">TOC</a>
  
  <xsl:if test="following-sibling::*[1]">
  <xsl:text> | </xsl:text>
  <a>
    <xsl:attribute name="href">
      #<xsl:value-of select="following-sibling::*[1]/@name"/>
    </xsl:attribute>next
  </a>
  </xsl:if>
  
  <!-- table -->
  <table border="1">
  <thead>
    <xsl:for-each select="col">
      <th>
        <code><xsl:value-of select="."/></code>
        <xsl:if test="@key='yes'">
          <xsl:text> (key)</xsl:text>
        </xsl:if>
        <br><xsl:value-of select="@def"/></br>        
      </th>
    </xsl:for-each>
  </thead>
  <tbody>
    <xsl:for-each select="row">
      <tr>
        <xsl:for-each select="td">
          <td>
            <xsl:variable name="pos" select="position()"/>
            <xsl:variable name="col" select="ancestor::table/col[position()=$pos]"/>
            <xsl:choose>
              <xsl:when test=".=''">
                <xsl:apply-templates select="."/>
              </xsl:when>
              <xsl:when test="substring($col, string-length($col), 1)='_'">
                <a><xsl:attribute name="href">#<xsl:value-of select="substring($col, 1, string-length($col)-1)"/>_<xsl:value-of select="."/></xsl:attribute>
                <xsl:apply-templates select="."/>
                </a>
              </xsl:when>
              <xsl:when test="$col/@key='yes'">
                <a><xsl:attribute name="name"><xsl:value-of select="ancestor::table/@name"/>_<xsl:value-of select="."/></xsl:attribute>
                <xsl:apply-templates select="."/>
                </a>
              </xsl:when>              
              <xsl:otherwise>
                <xsl:apply-templates select="."/>
              </xsl:otherwise>
            </xsl:choose>
          </td>
        </xsl:for-each>    
      </tr>
    </xsl:for-each>    
  </tbody>
  </table>      
</xsl:for-each>
</body>
</html>
</xsl:template>

<xsl:template match="/msi/table/row/td">
  <xsl:choose>
  
    <!-- external reference -->
    <xsl:when test="@href">
      <i>binary stream
        <a><xsl:attribute name="href">
          <xsl:value-of select="@href"/>
          </xsl:attribute>save to disk
        </a>
      </i>                  
    </xsl:when>
    
    <!-- NULL -->
    <xsl:when test=". = ''">
      <i>null</i>
    </xsl:when>
    
    <!-- base64 encoded binary data -->
    <xsl:when test="@dt:dt='bin.base64'">
      <i>binary stream 
      <xsl:if test="@md5">
        (<a>
          <xsl:attribute name="href">
            #<xsl:value-of select="ancestor::table/@name"/>
          </xsl:attribute>
          <xsl:attribute name="onClick">
            WriteBinData('<xsl:value-of select="@md5"/>')
          </xsl:attribute>save to disk</a>)
      </xsl:if>
      </i>
    </xsl:when>
    
    <!-- default -->              
    <xsl:otherwise>
      <code><xsl:value-of select="."/></code>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>