<?php
/**
  * wechat main php
  */
define("TOKEN", "ruofenghello");

$wechat = new  wechatCallback();
//varify token
if ($_GET["echostr"]) {
	$wechat->valid();
	exit;
}
else{
	$wechat->handle();
	exit;
}

class wechatCallback
{
	// globals
	$fromUsername;
	$toUsername;
	$createTime;
	$msgId;

	public function valid()
	{
		$echoStr = $_GET["echostr"];
		if($this->checkSignature())
		{
			echo $echoStr;
			exit;
		}
		else
		{
			echo "failure , check your TOKEN";
			exit;
		}
	}

	public function handle()
	{
		$postStr = $GLOBALS["HTTP_RAM_POST_DATA"];
		//extract POST data
		if ( !empty($postStr))
		{
			libxml_disable_entity_loader(true);
			$postObj = simplexml_load_string($postStr, 'SimpleXMLElement', LIBXML_NOCDATA);
			$GLOBALS[$fromUsername] = $postObj->FromUserName; //Sender's OpenID
			$GLOBALS[$toUsername] = $postObj->ToUserName;
			$GLOBALS[$createTime] = $postObj->CreateTime;
			$GLOBALS[$msgId] = $postObj->MsgId;
			$msgType = $postObj->MsgType;//text, image, voice, video, shortvideo, location, link
			
			switch ($msgType)
			{
				case "text":	$this->handleText($postObj); break;
				case "image":	$this->handleImage($postObj);break;
				case "voice":	$this->handleVoice($postObj);break;
				case "video":	$this->handleVideo($postObj);break;
				case "shortvideo":$this->handleShortVideo($postObj);break;
				case "location":$this->handleLocation($postObj);break;
				case "link":	$this->handleLink($postObj); break;
				default:error_log("handle xml error: unknown Msg Type");
			}
		}
		else
		{
			echo "";
			exit;
		}			
	}
	private function handleText($postObj)
	{
		$keyword = trim($postObj->Content);
		
		if (!empty( $keyword))
		{
			$contentStr = $keyword;
			replyText($contentStr);
		}
		else		
			echo "Pleasr input something...";
		

	}
	private function handleImage($postObj)
	{
		replyText("I got an Image.");
	}
	private function handleVoice($postObj)
	{
		replyText("I got an Voice.");
	}
	private function handleVideo($postObj)
	{
		replyText("I got an Video.");
	}
	private function handleShortVideo($postObj)
	{
		replyText("I got an ShortVideo.");
	}
	private function handleLocation($postObj)
	{
		replyText("I got an Location.");
	}
	private function handleLink($postObj)
	{
		replyText("I got an Link.");
	}

	//response text
	private function replyText($contentStr)
	{
		$textTpl = "<xml>
                                                        <ToUserName><![CDATA[%s]]></ToUserName>
                                                        <FromUserName><![CDATA[%s]]></FromUserName>
                                                        <CreateTime>%s</CreateTime>
                                                        <MsgType><![CDATA[%s]]></MsgType>
                                                        <Content><![CDATA[%s]]></Content>
                                                        <FuncFlag>0</FuncFlag>
                                                        </xml>";
		$msgType = "text";
		$resultStr = sprintf($textTpl,$GLOBALS[$fromUsername],$GLOBALS[$toUsername],time(),$msgType,$contentStr);
		echo $resultStr;	
	}

	private function checkSignature()
	{
		if (!define("TOKEN")) {
			throw new Exception('TOKEN is not defined!');
		}
		$signature = $_GET["signature"];
        	$timestamp = $_GET["timestamp"];
       	 	$nonce = $_GET["nonce"];

                $token = TOKEN;
                $tmpArr = array($token, $timestamp, $nonce);
        	// use SORT_STRING rule
                sort($tmpArr, SORT_STRING);
                $tmpStr = implode( $tmpArr );
		$tmpStr = sha1( $tmpStr );

                if( $tmpStr == $signature ){
                        return true;
                }else{
                        return false;
                }
        }
}

			


