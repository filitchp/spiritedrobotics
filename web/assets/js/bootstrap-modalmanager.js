  


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>bootstrap-modal/js/bootstrap-modalmanager.js at master · jschr/bootstrap-modal · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <link rel="logo" type="image/svg" href="http://github-media-downloads.s3.amazonaws.com/github-logo.svg" />
    <meta name="msapplication-TileImage" content="/windows-tile.png">
    <meta name="msapplication-TileColor" content="#ffffff">

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="xlfRCI1qb6oB5Jiyqc3k+Z7R1y2GZZHjbPZgktrsH/4=" name="csrf-token" />

    <link href="https://a248.e.akamai.net/assets.github.com/assets/github-d19801bcdb7e76b2de0fc1cd1c633416f755eecd.css" media="screen" rel="stylesheet" type="text/css" />
    <link href="https://a248.e.akamai.net/assets.github.com/assets/github2-baebc37fb76929295926c0a3aa868e1ad10e392a.css" media="screen" rel="stylesheet" type="text/css" />
    


      <script src="https://a248.e.akamai.net/assets.github.com/assets/frameworks-898c2db1f151d566cfe6a57c33338e30b3b75033.js" type="text/javascript"></script>
      <script src="https://a248.e.akamai.net/assets.github.com/assets/github-55d0b25fa303ea9d12ca9678c949b97dc38300cb.js" type="text/javascript"></script>
      
      <meta http-equiv="x-pjax-version" content="664b7279ade18884e11e295242b0a2b5">

        <link data-pjax-transient rel='permalink' href='/jschr/bootstrap-modal/blob/ba13b39354a7d2ee5167dfc9ac40a88eee79c847/js/bootstrap-modalmanager.js'>
    <meta property="og:title" content="bootstrap-modal"/>
    <meta property="og:type" content="githubog:gitrepository"/>
    <meta property="og:url" content="https://github.com/jschr/bootstrap-modal"/>
    <meta property="og:image" content="https://secure.gravatar.com/avatar/e5617cf700939d1bb113ed6fc711b831?s=420&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png"/>
    <meta property="og:site_name" content="GitHub"/>
    <meta property="og:description" content="bootstrap-modal - Extends the default Bootstrap Modal class. Responsive, stackable, ajax and more."/>
    <meta property="twitter:card" content="summary"/>
    <meta property="twitter:site" content="@GitHub">
    <meta property="twitter:title" content="jschr/bootstrap-modal"/>

    <meta name="description" content="bootstrap-modal - Extends the default Bootstrap Modal class. Responsive, stackable, ajax and more." />

  <link href="https://github.com/jschr/bootstrap-modal/commits/master.atom" rel="alternate" title="Recent Commits to bootstrap-modal:master" type="application/atom+xml" />

  </head>


  <body class="logged_out page-blob  vis-public env-production  ">
    <div id="wrapper">

      

      

      

      


        <div class="header header-logged-out">
          <div class="container clearfix">

            <a class="header-logo-wordmark" href="https://github.com/">
              <img alt="GitHub" class="github-logo-4x" height="30" src="https://a248.e.akamai.net/assets.github.com/images/modules/header/logov7@4x.png?1340659511" />
              <img alt="GitHub" class="github-logo-4x-hover" height="30" src="https://a248.e.akamai.net/assets.github.com/images/modules/header/logov7@4x-hover.png?1340659511" />
            </a>

              
<ul class="top-nav">
    <li class="explore"><a href="https://github.com/explore">Explore GitHub</a></li>
  <li class="search"><a href="https://github.com/search">Search</a></li>
  <li class="features"><a href="https://github.com/features">Features</a></li>
    <li class="blog"><a href="https://github.com/blog">Blog</a></li>
</ul>


            <div class="header-actions">
                <a class="button primary" href="https://github.com/signup">Sign up for free</a>
              <a class="button" href="https://github.com/login?return_to=%2Fjschr%2Fbootstrap-modal%2Fblob%2Fmaster%2Fjs%2Fbootstrap-modalmanager.js">Sign in</a>
            </div>

          </div>
        </div>


      

      


            <div class="site hfeed" itemscope itemtype="http://schema.org/WebPage">
      <div class="hentry">
        
        <div class="pagehead repohead instapaper_ignore readability-menu ">
          <div class="container">
            <div class="title-actions-bar">
              


<ul class="pagehead-actions">



    <li>
      <a href="/login?return_to=%2Fjschr%2Fbootstrap-modal"
        class="minibutton js-toggler-target star-button entice tooltipped upwards"
        title="You must be signed in to use this feature" rel="nofollow">
        <span class="mini-icon mini-icon-star"></span>Star
      </a>
      <a class="social-count js-social-count" href="/jschr/bootstrap-modal/stargazers">
        2,206
      </a>
    </li>
    <li>
      <a href="/login?return_to=%2Fjschr%2Fbootstrap-modal"
        class="minibutton js-toggler-target fork-button entice tooltipped upwards"
        title="You must be signed in to fork a repository" rel="nofollow">
        <span class="mini-icon mini-icon-fork"></span>Fork
      </a>
      <a href="/jschr/bootstrap-modal/network" class="social-count">
        197
      </a>
    </li>
</ul>

              <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
                <span class="repo-label"><span>public</span></span>
                <span class="mega-icon mega-icon-public-repo"></span>
                <span class="author vcard">
                  <a href="/jschr" class="url fn" itemprop="url" rel="author">
                  <span itemprop="title">jschr</span>
                  </a></span> /
                <strong><a href="/jschr/bootstrap-modal" class="js-current-repository">bootstrap-modal</a></strong>
              </h1>
            </div>

            
  <ul class="tabs">
    <li><a href="/jschr/bootstrap-modal" class="selected" highlight="repo_source repo_downloads repo_commits repo_tags repo_branches">Code</a></li>
    <li><a href="/jschr/bootstrap-modal/network" highlight="repo_network">Network</a></li>
    <li><a href="/jschr/bootstrap-modal/pulls" highlight="repo_pulls">Pull Requests <span class='counter'>2</span></a></li>

      <li><a href="/jschr/bootstrap-modal/issues" highlight="repo_issues">Issues <span class='counter'>17</span></a></li>

      <li><a href="/jschr/bootstrap-modal/wiki" highlight="repo_wiki">Wiki</a></li>


    <li><a href="/jschr/bootstrap-modal/graphs" highlight="repo_graphs repo_contributors">Graphs</a></li>


  </ul>
  
<div class="tabnav">

  <span class="tabnav-right">
    <ul class="tabnav-tabs">
          <li><a href="/jschr/bootstrap-modal/tags" class="tabnav-tab" highlight="repo_tags">Tags <span class="counter ">1</span></a></li>
    </ul>
    
  </span>

  <div class="tabnav-widget scope">


    <div class="select-menu js-menu-container js-select-menu js-branch-menu">
      <a class="minibutton select-menu-button js-menu-target" data-hotkey="w" data-ref="master">
        <span class="mini-icon mini-icon-branch"></span>
        <i>branch:</i>
        <span class="js-select-button">master</span>
      </a>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container js-select-menu-pane">

        <div class="select-menu-modal js-select-menu-pane">
          <div class="select-menu-header">
            <span class="select-menu-title">Switch branches/tags</span>
            <span class="mini-icon mini-icon-remove-close js-menu-close"></span>
          </div> <!-- /.select-menu-header -->

          <div class="select-menu-filters">
            <div class="select-menu-text-filter">
              <input type="text" id="commitish-filter-field" class="js-select-menu-text-filter js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
            </div> <!-- /.select-menu-text-filter -->
            <div class="select-menu-tabs">
              <ul>
                <li class="select-menu-tab">
                  <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
                </li>
                <li class="select-menu-tab">
                  <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
                </li>
              </ul>
            </div><!-- /.select-menu-tabs -->
          </div><!-- /.select-menu-filters -->

          <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket css-truncate" data-tab-filter="branches" data-filterable-for="commitish-filter-field" data-filterable-type="substring">


              <div class="select-menu-item js-navigation-item js-navigation-target ">
                <span class="select-menu-item-icon mini-icon mini-icon-confirm"></span>
                <a href="/jschr/bootstrap-modal/blob/gh-pages/js/bootstrap-modalmanager.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="gh-pages" rel="nofollow" title="gh-pages">gh-pages</a>
              </div> <!-- /.select-menu-item -->
              <div class="select-menu-item js-navigation-item js-navigation-target selected">
                <span class="select-menu-item-icon mini-icon mini-icon-confirm"></span>
                <a href="/jschr/bootstrap-modal/blob/master/js/bootstrap-modalmanager.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" rel="nofollow" title="master">master</a>
              </div> <!-- /.select-menu-item -->

              <div class="select-menu-no-results js-not-filterable">Nothing to show</div>
          </div> <!-- /.select-menu-list -->


          <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket css-truncate" data-tab-filter="tags" data-filterable-for="commitish-filter-field" data-filterable-type="substring">

              <div class="select-menu-item js-navigation-item js-navigation-target ">
                <span class="select-menu-item-icon mini-icon mini-icon-confirm"></span>
                <a href="/jschr/bootstrap-modal/blob/2.1.0/js/bootstrap-modalmanager.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="2.1.0" rel="nofollow" title="2.1.0">2.1.0</a>
              </div> <!-- /.select-menu-item -->

            <div class="select-menu-no-results js-not-filterable">Nothing to show</div>

          </div> <!-- /.select-menu-list -->

        </div> <!-- /.select-menu-modal -->
      </div> <!-- /.select-menu-modal-holder -->
    </div> <!-- /.select-menu -->

  </div> <!-- /.scope -->

  <ul class="tabnav-tabs">
    <li><a href="/jschr/bootstrap-modal" class="selected tabnav-tab" highlight="repo_source">Files</a></li>
    <li><a href="/jschr/bootstrap-modal/commits/master" class="tabnav-tab" highlight="repo_commits">Commits</a></li>
    <li><a href="/jschr/bootstrap-modal/branches" class="tabnav-tab" highlight="repo_branches" rel="nofollow">Branches <span class="counter ">2</span></a></li>
  </ul>

</div>

  
  
  


            
          </div>
        </div><!-- /.repohead -->

        <div id="js-repo-pjax-container" class="container context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:9b079a15ebfcabae590850657aaca956 -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:9b079a15ebfcabae590850657aaca956 -->


<div id="slider">
    <div class="frame-meta">

      <p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

        <div class="breadcrumb">
          <span class='bold'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/jschr/bootstrap-modal" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">bootstrap-modal</span></a></span></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/jschr/bootstrap-modal/tree/master/js" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">js</span></a></span><span class="separator"> / </span><strong class="final-path">bootstrap-modalmanager.js</strong> <span class="js-zeroclipboard zeroclipboard-button" data-clipboard-text="js/bootstrap-modalmanager.js" data-copied-hint="copied!" title="copy to clipboard"><span class="mini-icon mini-icon-clipboard"></span></span>
        </div>

      <a href="/jschr/bootstrap-modal/find/master" class="js-slide-to" data-hotkey="t" style="display:none">Show File Finder</a>


        
  <div class="commit file-history-tease">
    <img class="main-avatar" height="24" src="https://secure.gravatar.com/avatar/c036cacc476ff03266fac8b91493c30d?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
    <span class="author"><span rel="author">Brian Armstrong</span></span>
    <time class="js-relative-date" datetime="2013-02-08T17:32:29-08:00" title="2013-02-08 17:32:29">February 08, 2013</time>
    <div class="commit-title">
        <a href="/jschr/bootstrap-modal/commit/1ef4d84712a244985b0d2254808ca54650abb703" class="message">migrate triggerHandler to trigger</a>
    </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>2</strong> contributors</a></p>
          <a class="avatar tooltipped downwards" title="jschr" href="/jschr/bootstrap-modal/commits/master/js/bootstrap-modalmanager.js?author=jschr"><img height="20" src="https://secure.gravatar.com/avatar/e5617cf700939d1bb113ed6fc711b831?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>
    <a class="avatar tooltipped downwards" title="mystix" href="/jschr/bootstrap-modal/commits/master/js/bootstrap-modalmanager.js?author=mystix"><img height="20" src="https://secure.gravatar.com/avatar/697349b23f1d977e04c0dd7bc1f99727?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>


    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2>Users on GitHub who have contributed to this file</h2>
      <ul class="facebox-user-list">
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/e5617cf700939d1bb113ed6fc711b831?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/jschr">jschr</a>
        </li>
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/697349b23f1d977e04c0dd7bc1f99727?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/mystix">mystix</a>
        </li>
      </ul>
    </div>
  </div>


    </div><!-- ./.frame-meta -->

    <div class="frames">
      <div class="frame" data-permalink-url="/jschr/bootstrap-modal/blob/ba13b39354a7d2ee5167dfc9ac40a88eee79c847/js/bootstrap-modalmanager.js" data-title="bootstrap-modal/js/bootstrap-modalmanager.js at master · jschr/bootstrap-modal · GitHub" data-type="blob">

        <div id="files" class="bubble">
          <div class="file">
            <div class="meta">
              <div class="info">
                <span class="icon"><b class="mini-icon mini-icon-text-file"></b></span>
                <span class="mode" title="File Mode">file</span>
                  <span>413 lines (303 sloc)</span>
                <span>10.652 kb</span>
              </div>
              <div class="actions">
                <div class="button-group">
                      <a class="minibutton js-entice" href=""
                         data-entice="You must be signed in and on a branch to make or propose changes">Edit</a>
                  <a href="/jschr/bootstrap-modal/raw/master/js/bootstrap-modalmanager.js" class="button minibutton " id="raw-url">Raw</a>
                    <a href="/jschr/bootstrap-modal/blame/master/js/bootstrap-modalmanager.js" class="button minibutton ">Blame</a>
                  <a href="/jschr/bootstrap-modal/commits/master/js/bootstrap-modalmanager.js" class="button minibutton " rel="nofollow">History</a>
                </div><!-- /.button-group -->
              </div><!-- /.actions -->

            </div>
                <div class="data type-javascript js-blob-data">
      <table cellpadding="0" cellspacing="0" class="lines">
        <tr>
          <td>
            <pre class="line_numbers"><span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>
<span id="L162" rel="#L162">162</span>
<span id="L163" rel="#L163">163</span>
<span id="L164" rel="#L164">164</span>
<span id="L165" rel="#L165">165</span>
<span id="L166" rel="#L166">166</span>
<span id="L167" rel="#L167">167</span>
<span id="L168" rel="#L168">168</span>
<span id="L169" rel="#L169">169</span>
<span id="L170" rel="#L170">170</span>
<span id="L171" rel="#L171">171</span>
<span id="L172" rel="#L172">172</span>
<span id="L173" rel="#L173">173</span>
<span id="L174" rel="#L174">174</span>
<span id="L175" rel="#L175">175</span>
<span id="L176" rel="#L176">176</span>
<span id="L177" rel="#L177">177</span>
<span id="L178" rel="#L178">178</span>
<span id="L179" rel="#L179">179</span>
<span id="L180" rel="#L180">180</span>
<span id="L181" rel="#L181">181</span>
<span id="L182" rel="#L182">182</span>
<span id="L183" rel="#L183">183</span>
<span id="L184" rel="#L184">184</span>
<span id="L185" rel="#L185">185</span>
<span id="L186" rel="#L186">186</span>
<span id="L187" rel="#L187">187</span>
<span id="L188" rel="#L188">188</span>
<span id="L189" rel="#L189">189</span>
<span id="L190" rel="#L190">190</span>
<span id="L191" rel="#L191">191</span>
<span id="L192" rel="#L192">192</span>
<span id="L193" rel="#L193">193</span>
<span id="L194" rel="#L194">194</span>
<span id="L195" rel="#L195">195</span>
<span id="L196" rel="#L196">196</span>
<span id="L197" rel="#L197">197</span>
<span id="L198" rel="#L198">198</span>
<span id="L199" rel="#L199">199</span>
<span id="L200" rel="#L200">200</span>
<span id="L201" rel="#L201">201</span>
<span id="L202" rel="#L202">202</span>
<span id="L203" rel="#L203">203</span>
<span id="L204" rel="#L204">204</span>
<span id="L205" rel="#L205">205</span>
<span id="L206" rel="#L206">206</span>
<span id="L207" rel="#L207">207</span>
<span id="L208" rel="#L208">208</span>
<span id="L209" rel="#L209">209</span>
<span id="L210" rel="#L210">210</span>
<span id="L211" rel="#L211">211</span>
<span id="L212" rel="#L212">212</span>
<span id="L213" rel="#L213">213</span>
<span id="L214" rel="#L214">214</span>
<span id="L215" rel="#L215">215</span>
<span id="L216" rel="#L216">216</span>
<span id="L217" rel="#L217">217</span>
<span id="L218" rel="#L218">218</span>
<span id="L219" rel="#L219">219</span>
<span id="L220" rel="#L220">220</span>
<span id="L221" rel="#L221">221</span>
<span id="L222" rel="#L222">222</span>
<span id="L223" rel="#L223">223</span>
<span id="L224" rel="#L224">224</span>
<span id="L225" rel="#L225">225</span>
<span id="L226" rel="#L226">226</span>
<span id="L227" rel="#L227">227</span>
<span id="L228" rel="#L228">228</span>
<span id="L229" rel="#L229">229</span>
<span id="L230" rel="#L230">230</span>
<span id="L231" rel="#L231">231</span>
<span id="L232" rel="#L232">232</span>
<span id="L233" rel="#L233">233</span>
<span id="L234" rel="#L234">234</span>
<span id="L235" rel="#L235">235</span>
<span id="L236" rel="#L236">236</span>
<span id="L237" rel="#L237">237</span>
<span id="L238" rel="#L238">238</span>
<span id="L239" rel="#L239">239</span>
<span id="L240" rel="#L240">240</span>
<span id="L241" rel="#L241">241</span>
<span id="L242" rel="#L242">242</span>
<span id="L243" rel="#L243">243</span>
<span id="L244" rel="#L244">244</span>
<span id="L245" rel="#L245">245</span>
<span id="L246" rel="#L246">246</span>
<span id="L247" rel="#L247">247</span>
<span id="L248" rel="#L248">248</span>
<span id="L249" rel="#L249">249</span>
<span id="L250" rel="#L250">250</span>
<span id="L251" rel="#L251">251</span>
<span id="L252" rel="#L252">252</span>
<span id="L253" rel="#L253">253</span>
<span id="L254" rel="#L254">254</span>
<span id="L255" rel="#L255">255</span>
<span id="L256" rel="#L256">256</span>
<span id="L257" rel="#L257">257</span>
<span id="L258" rel="#L258">258</span>
<span id="L259" rel="#L259">259</span>
<span id="L260" rel="#L260">260</span>
<span id="L261" rel="#L261">261</span>
<span id="L262" rel="#L262">262</span>
<span id="L263" rel="#L263">263</span>
<span id="L264" rel="#L264">264</span>
<span id="L265" rel="#L265">265</span>
<span id="L266" rel="#L266">266</span>
<span id="L267" rel="#L267">267</span>
<span id="L268" rel="#L268">268</span>
<span id="L269" rel="#L269">269</span>
<span id="L270" rel="#L270">270</span>
<span id="L271" rel="#L271">271</span>
<span id="L272" rel="#L272">272</span>
<span id="L273" rel="#L273">273</span>
<span id="L274" rel="#L274">274</span>
<span id="L275" rel="#L275">275</span>
<span id="L276" rel="#L276">276</span>
<span id="L277" rel="#L277">277</span>
<span id="L278" rel="#L278">278</span>
<span id="L279" rel="#L279">279</span>
<span id="L280" rel="#L280">280</span>
<span id="L281" rel="#L281">281</span>
<span id="L282" rel="#L282">282</span>
<span id="L283" rel="#L283">283</span>
<span id="L284" rel="#L284">284</span>
<span id="L285" rel="#L285">285</span>
<span id="L286" rel="#L286">286</span>
<span id="L287" rel="#L287">287</span>
<span id="L288" rel="#L288">288</span>
<span id="L289" rel="#L289">289</span>
<span id="L290" rel="#L290">290</span>
<span id="L291" rel="#L291">291</span>
<span id="L292" rel="#L292">292</span>
<span id="L293" rel="#L293">293</span>
<span id="L294" rel="#L294">294</span>
<span id="L295" rel="#L295">295</span>
<span id="L296" rel="#L296">296</span>
<span id="L297" rel="#L297">297</span>
<span id="L298" rel="#L298">298</span>
<span id="L299" rel="#L299">299</span>
<span id="L300" rel="#L300">300</span>
<span id="L301" rel="#L301">301</span>
<span id="L302" rel="#L302">302</span>
<span id="L303" rel="#L303">303</span>
<span id="L304" rel="#L304">304</span>
<span id="L305" rel="#L305">305</span>
<span id="L306" rel="#L306">306</span>
<span id="L307" rel="#L307">307</span>
<span id="L308" rel="#L308">308</span>
<span id="L309" rel="#L309">309</span>
<span id="L310" rel="#L310">310</span>
<span id="L311" rel="#L311">311</span>
<span id="L312" rel="#L312">312</span>
<span id="L313" rel="#L313">313</span>
<span id="L314" rel="#L314">314</span>
<span id="L315" rel="#L315">315</span>
<span id="L316" rel="#L316">316</span>
<span id="L317" rel="#L317">317</span>
<span id="L318" rel="#L318">318</span>
<span id="L319" rel="#L319">319</span>
<span id="L320" rel="#L320">320</span>
<span id="L321" rel="#L321">321</span>
<span id="L322" rel="#L322">322</span>
<span id="L323" rel="#L323">323</span>
<span id="L324" rel="#L324">324</span>
<span id="L325" rel="#L325">325</span>
<span id="L326" rel="#L326">326</span>
<span id="L327" rel="#L327">327</span>
<span id="L328" rel="#L328">328</span>
<span id="L329" rel="#L329">329</span>
<span id="L330" rel="#L330">330</span>
<span id="L331" rel="#L331">331</span>
<span id="L332" rel="#L332">332</span>
<span id="L333" rel="#L333">333</span>
<span id="L334" rel="#L334">334</span>
<span id="L335" rel="#L335">335</span>
<span id="L336" rel="#L336">336</span>
<span id="L337" rel="#L337">337</span>
<span id="L338" rel="#L338">338</span>
<span id="L339" rel="#L339">339</span>
<span id="L340" rel="#L340">340</span>
<span id="L341" rel="#L341">341</span>
<span id="L342" rel="#L342">342</span>
<span id="L343" rel="#L343">343</span>
<span id="L344" rel="#L344">344</span>
<span id="L345" rel="#L345">345</span>
<span id="L346" rel="#L346">346</span>
<span id="L347" rel="#L347">347</span>
<span id="L348" rel="#L348">348</span>
<span id="L349" rel="#L349">349</span>
<span id="L350" rel="#L350">350</span>
<span id="L351" rel="#L351">351</span>
<span id="L352" rel="#L352">352</span>
<span id="L353" rel="#L353">353</span>
<span id="L354" rel="#L354">354</span>
<span id="L355" rel="#L355">355</span>
<span id="L356" rel="#L356">356</span>
<span id="L357" rel="#L357">357</span>
<span id="L358" rel="#L358">358</span>
<span id="L359" rel="#L359">359</span>
<span id="L360" rel="#L360">360</span>
<span id="L361" rel="#L361">361</span>
<span id="L362" rel="#L362">362</span>
<span id="L363" rel="#L363">363</span>
<span id="L364" rel="#L364">364</span>
<span id="L365" rel="#L365">365</span>
<span id="L366" rel="#L366">366</span>
<span id="L367" rel="#L367">367</span>
<span id="L368" rel="#L368">368</span>
<span id="L369" rel="#L369">369</span>
<span id="L370" rel="#L370">370</span>
<span id="L371" rel="#L371">371</span>
<span id="L372" rel="#L372">372</span>
<span id="L373" rel="#L373">373</span>
<span id="L374" rel="#L374">374</span>
<span id="L375" rel="#L375">375</span>
<span id="L376" rel="#L376">376</span>
<span id="L377" rel="#L377">377</span>
<span id="L378" rel="#L378">378</span>
<span id="L379" rel="#L379">379</span>
<span id="L380" rel="#L380">380</span>
<span id="L381" rel="#L381">381</span>
<span id="L382" rel="#L382">382</span>
<span id="L383" rel="#L383">383</span>
<span id="L384" rel="#L384">384</span>
<span id="L385" rel="#L385">385</span>
<span id="L386" rel="#L386">386</span>
<span id="L387" rel="#L387">387</span>
<span id="L388" rel="#L388">388</span>
<span id="L389" rel="#L389">389</span>
<span id="L390" rel="#L390">390</span>
<span id="L391" rel="#L391">391</span>
<span id="L392" rel="#L392">392</span>
<span id="L393" rel="#L393">393</span>
<span id="L394" rel="#L394">394</span>
<span id="L395" rel="#L395">395</span>
<span id="L396" rel="#L396">396</span>
<span id="L397" rel="#L397">397</span>
<span id="L398" rel="#L398">398</span>
<span id="L399" rel="#L399">399</span>
<span id="L400" rel="#L400">400</span>
<span id="L401" rel="#L401">401</span>
<span id="L402" rel="#L402">402</span>
<span id="L403" rel="#L403">403</span>
<span id="L404" rel="#L404">404</span>
<span id="L405" rel="#L405">405</span>
<span id="L406" rel="#L406">406</span>
<span id="L407" rel="#L407">407</span>
<span id="L408" rel="#L408">408</span>
<span id="L409" rel="#L409">409</span>
<span id="L410" rel="#L410">410</span>
<span id="L411" rel="#L411">411</span>
<span id="L412" rel="#L412">412</span>
</pre>
          </td>
          <td width="100%">
                  <div class="highlight"><pre><div class='line' id='LC1'><span class="cm">/* ===========================================================</span></div><div class='line' id='LC2'><span class="cm"> * bootstrap-modalmanager.js v2.1</span></div><div class='line' id='LC3'><span class="cm"> * ===========================================================</span></div><div class='line' id='LC4'><span class="cm"> * Copyright 2012 Jordan Schroter.</span></div><div class='line' id='LC5'><span class="cm"> *</span></div><div class='line' id='LC6'><span class="cm"> * Licensed under the Apache License, Version 2.0 (the &quot;License&quot;);</span></div><div class='line' id='LC7'><span class="cm"> * you may not use this file except in compliance with the License.</span></div><div class='line' id='LC8'><span class="cm"> * You may obtain a copy of the License at</span></div><div class='line' id='LC9'><span class="cm"> *</span></div><div class='line' id='LC10'><span class="cm"> * http://www.apache.org/licenses/LICENSE-2.0</span></div><div class='line' id='LC11'><span class="cm"> *</span></div><div class='line' id='LC12'><span class="cm"> * Unless required by applicable law or agreed to in writing, software</span></div><div class='line' id='LC13'><span class="cm"> * distributed under the License is distributed on an &quot;AS IS&quot; BASIS,</span></div><div class='line' id='LC14'><span class="cm"> * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.</span></div><div class='line' id='LC15'><span class="cm"> * See the License for the specific language governing permissions and</span></div><div class='line' id='LC16'><span class="cm"> * limitations under the License.</span></div><div class='line' id='LC17'><span class="cm"> * ========================================================== */</span></div><div class='line' id='LC18'><br/></div><div class='line' id='LC19'><span class="o">!</span><span class="kd">function</span> <span class="p">(</span><span class="nx">$</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC20'><br/></div><div class='line' id='LC21'>	<span class="s2">&quot;use strict&quot;</span><span class="p">;</span> <span class="c1">// jshint ;_;</span></div><div class='line' id='LC22'><br/></div><div class='line' id='LC23'>	<span class="cm">/* MODAL MANAGER CLASS DEFINITION</span></div><div class='line' id='LC24'><span class="cm">	* ====================== */</span></div><div class='line' id='LC25'><br/></div><div class='line' id='LC26'>	<span class="kd">var</span> <span class="nx">ModalManager</span> <span class="o">=</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">element</span><span class="p">,</span> <span class="nx">options</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC27'>		<span class="k">this</span><span class="p">.</span><span class="nx">init</span><span class="p">(</span><span class="nx">element</span><span class="p">,</span> <span class="nx">options</span><span class="p">);</span></div><div class='line' id='LC28'>	<span class="p">};</span></div><div class='line' id='LC29'><br/></div><div class='line' id='LC30'>	<span class="nx">ModalManager</span><span class="p">.</span><span class="nx">prototype</span> <span class="o">=</span> <span class="p">{</span></div><div class='line' id='LC31'><br/></div><div class='line' id='LC32'>		<span class="nx">constructor</span><span class="o">:</span> <span class="nx">ModalManager</span><span class="p">,</span></div><div class='line' id='LC33'><br/></div><div class='line' id='LC34'>		<span class="nx">init</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">element</span><span class="p">,</span> <span class="nx">options</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC35'>			<span class="k">this</span><span class="p">.</span><span class="nx">$element</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="nx">element</span><span class="p">);</span></div><div class='line' id='LC36'>			<span class="k">this</span><span class="p">.</span><span class="nx">options</span> <span class="o">=</span> <span class="nx">$</span><span class="p">.</span><span class="nx">extend</span><span class="p">({},</span> <span class="nx">$</span><span class="p">.</span><span class="nx">fn</span><span class="p">.</span><span class="nx">modalmanager</span><span class="p">.</span><span class="nx">defaults</span><span class="p">,</span> <span class="k">this</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">data</span><span class="p">(),</span> <span class="k">typeof</span> <span class="nx">options</span> <span class="o">==</span> <span class="s1">&#39;object&#39;</span> <span class="o">&amp;&amp;</span> <span class="nx">options</span><span class="p">);</span></div><div class='line' id='LC37'>			<span class="k">this</span><span class="p">.</span><span class="nx">stack</span> <span class="o">=</span> <span class="p">[];</span></div><div class='line' id='LC38'>			<span class="k">this</span><span class="p">.</span><span class="nx">backdropCount</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC39'><br/></div><div class='line' id='LC40'>			<span class="k">if</span> <span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">options</span><span class="p">.</span><span class="nx">resize</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC41'>				<span class="kd">var</span> <span class="nx">resizeTimeout</span><span class="p">,</span></div><div class='line' id='LC42'>					<span class="nx">that</span> <span class="o">=</span> <span class="k">this</span><span class="p">;</span></div><div class='line' id='LC43'><br/></div><div class='line' id='LC44'>				<span class="nx">$</span><span class="p">(</span><span class="nb">window</span><span class="p">).</span><span class="nx">on</span><span class="p">(</span><span class="s1">&#39;resize.modal&#39;</span><span class="p">,</span> <span class="kd">function</span><span class="p">(){</span></div><div class='line' id='LC45'>					<span class="nx">resizeTimeout</span> <span class="o">&amp;&amp;</span> <span class="nx">clearTimeout</span><span class="p">(</span><span class="nx">resizeTimeout</span><span class="p">);</span></div><div class='line' id='LC46'>					<span class="nx">resizeTimeout</span> <span class="o">=</span> <span class="nx">setTimeout</span><span class="p">(</span><span class="kd">function</span><span class="p">(){</span></div><div class='line' id='LC47'>						<span class="k">for</span> <span class="p">(</span><span class="kd">var</span> <span class="nx">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="nx">i</span> <span class="o">&lt;</span> <span class="nx">that</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span><span class="p">;</span> <span class="nx">i</span><span class="o">++</span><span class="p">){</span></div><div class='line' id='LC48'>							<span class="nx">that</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">].</span><span class="nx">isShown</span> <span class="o">&amp;&amp;</span> <span class="nx">that</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">].</span><span class="nx">layout</span><span class="p">();</span></div><div class='line' id='LC49'>						<span class="p">}</span></div><div class='line' id='LC50'>					<span class="p">},</span> <span class="mi">10</span><span class="p">);</span></div><div class='line' id='LC51'>				<span class="p">});</span></div><div class='line' id='LC52'>			<span class="p">}</span></div><div class='line' id='LC53'>		<span class="p">},</span></div><div class='line' id='LC54'><br/></div><div class='line' id='LC55'>		<span class="nx">createModal</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">element</span><span class="p">,</span> <span class="nx">options</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC56'>			<span class="nx">$</span><span class="p">(</span><span class="nx">element</span><span class="p">).</span><span class="nx">modal</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">extend</span><span class="p">({</span> <span class="nx">manager</span><span class="o">:</span> <span class="k">this</span> <span class="p">},</span> <span class="nx">options</span><span class="p">));</span></div><div class='line' id='LC57'>		<span class="p">},</span></div><div class='line' id='LC58'><br/></div><div class='line' id='LC59'>		<span class="nx">appendModal</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC60'>			<span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">push</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC61'><br/></div><div class='line' id='LC62'>			<span class="kd">var</span> <span class="nx">that</span> <span class="o">=</span> <span class="k">this</span><span class="p">;</span></div><div class='line' id='LC63'><br/></div><div class='line' id='LC64'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">on</span><span class="p">(</span><span class="s1">&#39;show.modalmanager&#39;</span><span class="p">,</span> <span class="nx">targetIsSelf</span><span class="p">(</span><span class="kd">function</span> <span class="p">(</span><span class="nx">e</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC65'><br/></div><div class='line' id='LC66'>				<span class="kd">var</span> <span class="nx">showModal</span> <span class="o">=</span> <span class="kd">function</span><span class="p">(){</span></div><div class='line' id='LC67'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">isShown</span> <span class="o">=</span> <span class="kc">true</span><span class="p">;</span></div><div class='line' id='LC68'><br/></div><div class='line' id='LC69'>					<span class="kd">var</span> <span class="nx">transition</span> <span class="o">=</span> <span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span> <span class="o">&amp;&amp;</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">hasClass</span><span class="p">(</span><span class="s1">&#39;fade&#39;</span><span class="p">);</span></div><div class='line' id='LC70'><br/></div><div class='line' id='LC71'>					<span class="nx">that</span><span class="p">.</span><span class="nx">$element</span></div><div class='line' id='LC72'>						<span class="p">.</span><span class="nx">toggleClass</span><span class="p">(</span><span class="s1">&#39;modal-open&#39;</span><span class="p">,</span> <span class="nx">that</span><span class="p">.</span><span class="nx">hasOpenModal</span><span class="p">())</span></div><div class='line' id='LC73'>						<span class="p">.</span><span class="nx">toggleClass</span><span class="p">(</span><span class="s1">&#39;page-overflow&#39;</span><span class="p">,</span> <span class="nx">$</span><span class="p">(</span><span class="nb">window</span><span class="p">).</span><span class="nx">height</span><span class="p">()</span> <span class="o">&lt;</span> <span class="nx">that</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">height</span><span class="p">());</span></div><div class='line' id='LC74'><br/></div><div class='line' id='LC75'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">$parent</span> <span class="o">=</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">parent</span><span class="p">();</span></div><div class='line' id='LC76'><br/></div><div class='line' id='LC77'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">$container</span> <span class="o">=</span> <span class="nx">that</span><span class="p">.</span><span class="nx">createContainer</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC78'><br/></div><div class='line' id='LC79'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">appendTo</span><span class="p">(</span><span class="nx">modal</span><span class="p">.</span><span class="nx">$container</span><span class="p">);</span></div><div class='line' id='LC80'><br/></div><div class='line' id='LC81'>					<span class="nx">that</span><span class="p">.</span><span class="nx">backdrop</span><span class="p">(</span><span class="nx">modal</span><span class="p">,</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC82'><br/></div><div class='line' id='LC83'>						<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">show</span><span class="p">();</span></div><div class='line' id='LC84'><br/></div><div class='line' id='LC85'>						<span class="k">if</span> <span class="p">(</span><span class="nx">transition</span><span class="p">)</span> <span class="p">{</span>       </div><div class='line' id='LC86'>							<span class="c1">//modal.$element[0].style.display = &#39;run-in&#39;;       </span></div><div class='line' id='LC87'>							<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">[</span><span class="mi">0</span><span class="p">].</span><span class="nx">offsetWidth</span><span class="p">;</span></div><div class='line' id='LC88'>							<span class="c1">//modal.$element.one($.support.transition.end, function () { modal.$element[0].style.display = &#39;block&#39; });  </span></div><div class='line' id='LC89'>						<span class="p">}</span></div><div class='line' id='LC90'><br/></div><div class='line' id='LC91'>						<span class="nx">modal</span><span class="p">.</span><span class="nx">layout</span><span class="p">();</span></div><div class='line' id='LC92'><br/></div><div class='line' id='LC93'>						<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span></div><div class='line' id='LC94'>							<span class="p">.</span><span class="nx">addClass</span><span class="p">(</span><span class="s1">&#39;in&#39;</span><span class="p">)</span></div><div class='line' id='LC95'>							<span class="p">.</span><span class="nx">attr</span><span class="p">(</span><span class="s1">&#39;aria-hidden&#39;</span><span class="p">,</span> <span class="kc">false</span><span class="p">);</span></div><div class='line' id='LC96'><br/></div><div class='line' id='LC97'>						<span class="kd">var</span> <span class="nx">complete</span> <span class="o">=</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC98'>							<span class="nx">that</span><span class="p">.</span><span class="nx">setFocus</span><span class="p">();</span></div><div class='line' id='LC99'>							<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">trigger</span><span class="p">(</span><span class="s1">&#39;shown&#39;</span><span class="p">);</span></div><div class='line' id='LC100'>						<span class="p">};</span></div><div class='line' id='LC101'><br/></div><div class='line' id='LC102'>						<span class="nx">transition</span> <span class="o">?</span></div><div class='line' id='LC103'>							<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">one</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span><span class="p">.</span><span class="nx">end</span><span class="p">,</span> <span class="nx">complete</span><span class="p">)</span> <span class="o">:</span></div><div class='line' id='LC104'>							<span class="nx">complete</span><span class="p">();</span></div><div class='line' id='LC105'>					<span class="p">});</span></div><div class='line' id='LC106'>				<span class="p">};</span></div><div class='line' id='LC107'><br/></div><div class='line' id='LC108'>				<span class="nx">modal</span><span class="p">.</span><span class="nx">options</span><span class="p">.</span><span class="nx">replace</span> <span class="o">?</span></div><div class='line' id='LC109'>					<span class="nx">that</span><span class="p">.</span><span class="nx">replace</span><span class="p">(</span><span class="nx">showModal</span><span class="p">)</span> <span class="o">:</span></div><div class='line' id='LC110'>					<span class="nx">showModal</span><span class="p">();</span></div><div class='line' id='LC111'>			<span class="p">}));</span></div><div class='line' id='LC112'><br/></div><div class='line' id='LC113'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">on</span><span class="p">(</span><span class="s1">&#39;hidden.modalmanager&#39;</span><span class="p">,</span> <span class="nx">targetIsSelf</span><span class="p">(</span><span class="kd">function</span> <span class="p">(</span><span class="nx">e</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC114'><br/></div><div class='line' id='LC115'>				<span class="nx">that</span><span class="p">.</span><span class="nx">backdrop</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC116'><br/></div><div class='line' id='LC117'>				<span class="k">if</span> <span class="p">(</span><span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">){</span></div><div class='line' id='LC118'>					<span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span> <span class="o">&amp;&amp;</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">hasClass</span><span class="p">(</span><span class="s1">&#39;fade&#39;</span><span class="p">)</span> <span class="o">?</span></div><div class='line' id='LC119'>						<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">.</span><span class="nx">one</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span><span class="p">.</span><span class="nx">end</span><span class="p">,</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span> <span class="nx">that</span><span class="p">.</span><span class="nx">destroyModal</span><span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">})</span> <span class="o">:</span></div><div class='line' id='LC120'>						<span class="nx">that</span><span class="p">.</span><span class="nx">destroyModal</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC121'>				<span class="p">}</span> <span class="k">else</span> <span class="p">{</span></div><div class='line' id='LC122'>					<span class="nx">that</span><span class="p">.</span><span class="nx">destroyModal</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC123'>				<span class="p">}</span></div><div class='line' id='LC124'><br/></div><div class='line' id='LC125'>			<span class="p">}));</span></div><div class='line' id='LC126'><br/></div><div class='line' id='LC127'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">on</span><span class="p">(</span><span class="s1">&#39;destroy.modalmanager&#39;</span><span class="p">,</span> <span class="nx">targetIsSelf</span><span class="p">(</span><span class="kd">function</span> <span class="p">(</span><span class="nx">e</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC128'>				<span class="nx">that</span><span class="p">.</span><span class="nx">removeModal</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC129'>			<span class="p">}));</span></div><div class='line' id='LC130'><br/></div><div class='line' id='LC131'>		<span class="p">},</span></div><div class='line' id='LC132'><br/></div><div class='line' id='LC133'>		<span class="nx">destroyModal</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC134'><br/></div><div class='line' id='LC135'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">destroy</span><span class="p">();</span></div><div class='line' id='LC136'><br/></div><div class='line' id='LC137'>			<span class="kd">var</span> <span class="nx">hasOpenModal</span> <span class="o">=</span> <span class="k">this</span><span class="p">.</span><span class="nx">hasOpenModal</span><span class="p">();</span></div><div class='line' id='LC138'><br/></div><div class='line' id='LC139'>			<span class="k">this</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">toggleClass</span><span class="p">(</span><span class="s1">&#39;modal-open&#39;</span><span class="p">,</span> <span class="nx">hasOpenModal</span><span class="p">);</span></div><div class='line' id='LC140'><br/></div><div class='line' id='LC141'>			<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="nx">hasOpenModal</span><span class="p">){</span></div><div class='line' id='LC142'>				<span class="k">this</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">removeClass</span><span class="p">(</span><span class="s1">&#39;page-overflow&#39;</span><span class="p">);</span></div><div class='line' id='LC143'>			<span class="p">}</span></div><div class='line' id='LC144'><br/></div><div class='line' id='LC145'>			<span class="k">this</span><span class="p">.</span><span class="nx">removeContainer</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC146'><br/></div><div class='line' id='LC147'>			<span class="k">this</span><span class="p">.</span><span class="nx">setFocus</span><span class="p">();</span></div><div class='line' id='LC148'>		<span class="p">},</span></div><div class='line' id='LC149'><br/></div><div class='line' id='LC150'>		<span class="nx">hasOpenModal</span><span class="o">:</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC151'>			<span class="k">for</span> <span class="p">(</span><span class="kd">var</span> <span class="nx">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="nx">i</span> <span class="o">&lt;</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span><span class="p">;</span> <span class="nx">i</span><span class="o">++</span><span class="p">){</span></div><div class='line' id='LC152'>				<span class="k">if</span> <span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">].</span><span class="nx">isShown</span><span class="p">)</span> <span class="k">return</span> <span class="kc">true</span><span class="p">;</span></div><div class='line' id='LC153'>			<span class="p">}</span></div><div class='line' id='LC154'><br/></div><div class='line' id='LC155'>			<span class="k">return</span> <span class="kc">false</span><span class="p">;</span></div><div class='line' id='LC156'>		<span class="p">},</span></div><div class='line' id='LC157'><br/></div><div class='line' id='LC158'>		<span class="nx">setFocus</span><span class="o">:</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC159'>			<span class="kd">var</span> <span class="nx">topModal</span><span class="p">;</span></div><div class='line' id='LC160'><br/></div><div class='line' id='LC161'>			<span class="k">for</span> <span class="p">(</span><span class="kd">var</span> <span class="nx">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="nx">i</span> <span class="o">&lt;</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span><span class="p">;</span> <span class="nx">i</span><span class="o">++</span><span class="p">){</span></div><div class='line' id='LC162'>				<span class="k">if</span> <span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">].</span><span class="nx">isShown</span><span class="p">)</span> <span class="nx">topModal</span> <span class="o">=</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">];</span></div><div class='line' id='LC163'>			<span class="p">}</span></div><div class='line' id='LC164'><br/></div><div class='line' id='LC165'>			<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="nx">topModal</span><span class="p">)</span> <span class="k">return</span><span class="p">;</span></div><div class='line' id='LC166'><br/></div><div class='line' id='LC167'>			<span class="nx">topModal</span><span class="p">.</span><span class="nx">focus</span><span class="p">();</span></div><div class='line' id='LC168'><br/></div><div class='line' id='LC169'>		<span class="p">},</span></div><div class='line' id='LC170'><br/></div><div class='line' id='LC171'>		<span class="nx">removeModal</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC172'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">off</span><span class="p">(</span><span class="s1">&#39;.modalmanager&#39;</span><span class="p">);</span></div><div class='line' id='LC173'>			<span class="k">if</span> <span class="p">(</span><span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">)</span> <span class="k">this</span><span class="p">.</span><span class="nx">removeBackdrop</span><span class="p">.</span><span class="nx">call</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC174'>			<span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">splice</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">getIndexOfModal</span><span class="p">(</span><span class="nx">modal</span><span class="p">),</span> <span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC175'>		<span class="p">},</span></div><div class='line' id='LC176'><br/></div><div class='line' id='LC177'>		<span class="nx">getModalAt</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">index</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC178'>			<span class="k">return</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">index</span><span class="p">];</span></div><div class='line' id='LC179'>		<span class="p">},</span></div><div class='line' id='LC180'><br/></div><div class='line' id='LC181'>		<span class="nx">getIndexOfModal</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC182'>			<span class="k">for</span> <span class="p">(</span><span class="kd">var</span> <span class="nx">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="nx">i</span> <span class="o">&lt;</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span><span class="p">;</span> <span class="nx">i</span><span class="o">++</span><span class="p">){</span></div><div class='line' id='LC183'>				<span class="k">if</span> <span class="p">(</span><span class="nx">modal</span> <span class="o">===</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">])</span> <span class="k">return</span> <span class="nx">i</span><span class="p">;</span></div><div class='line' id='LC184'>			<span class="p">}</span></div><div class='line' id='LC185'>		<span class="p">},</span></div><div class='line' id='LC186'><br/></div><div class='line' id='LC187'>		<span class="nx">replace</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">callback</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC188'>			<span class="kd">var</span> <span class="nx">topModal</span><span class="p">;</span></div><div class='line' id='LC189'><br/></div><div class='line' id='LC190'>			<span class="k">for</span> <span class="p">(</span><span class="kd">var</span> <span class="nx">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="nx">i</span> <span class="o">&lt;</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span><span class="p">;</span> <span class="nx">i</span><span class="o">++</span><span class="p">){</span></div><div class='line' id='LC191'>				<span class="k">if</span> <span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">].</span><span class="nx">isShown</span><span class="p">)</span> <span class="nx">topModal</span> <span class="o">=</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">[</span><span class="nx">i</span><span class="p">];</span></div><div class='line' id='LC192'>			<span class="p">}</span></div><div class='line' id='LC193'><br/></div><div class='line' id='LC194'>			<span class="k">if</span> <span class="p">(</span><span class="nx">topModal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC195'>				<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span> <span class="o">=</span> <span class="nx">topModal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">;</span></div><div class='line' id='LC196'>				<span class="nx">topModal</span><span class="p">.</span><span class="nx">$backdrop</span> <span class="o">=</span> <span class="kc">null</span><span class="p">;</span></div><div class='line' id='LC197'><br/></div><div class='line' id='LC198'>				<span class="nx">callback</span> <span class="o">&amp;&amp;</span> <span class="nx">topModal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">one</span><span class="p">(</span><span class="s1">&#39;hidden&#39;</span><span class="p">,</span></div><div class='line' id='LC199'>					<span class="nx">targetIsSelf</span><span class="p">(</span> <span class="nx">$</span><span class="p">.</span><span class="nx">proxy</span><span class="p">(</span><span class="nx">callback</span><span class="p">,</span> <span class="k">this</span><span class="p">)</span> <span class="p">));</span></div><div class='line' id='LC200'><br/></div><div class='line' id='LC201'>				<span class="nx">topModal</span><span class="p">.</span><span class="nx">hide</span><span class="p">();</span></div><div class='line' id='LC202'>			<span class="p">}</span> <span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="nx">callback</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC203'>				<span class="nx">callback</span><span class="p">();</span></div><div class='line' id='LC204'>			<span class="p">}</span></div><div class='line' id='LC205'>		<span class="p">},</span></div><div class='line' id='LC206'><br/></div><div class='line' id='LC207'>		<span class="nx">removeBackdrop</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC208'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">.</span><span class="nx">remove</span><span class="p">();</span></div><div class='line' id='LC209'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span> <span class="o">=</span> <span class="kc">null</span><span class="p">;</span></div><div class='line' id='LC210'>		<span class="p">},</span></div><div class='line' id='LC211'><br/></div><div class='line' id='LC212'>		<span class="nx">createBackdrop</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">animate</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC213'>			<span class="kd">var</span> <span class="nx">$backdrop</span><span class="p">;</span></div><div class='line' id='LC214'><br/></div><div class='line' id='LC215'>			<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC216'>				<span class="nx">$backdrop</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="s1">&#39;&lt;div class=&quot;modal-backdrop &#39;</span> <span class="o">+</span> <span class="nx">animate</span> <span class="o">+</span> <span class="s1">&#39;&quot; /&gt;&#39;</span><span class="p">)</span></div><div class='line' id='LC217'>					<span class="p">.</span><span class="nx">appendTo</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">$element</span><span class="p">);</span></div><div class='line' id='LC218'>			<span class="p">}</span> <span class="k">else</span> <span class="p">{</span></div><div class='line' id='LC219'>				<span class="nx">$backdrop</span> <span class="o">=</span> <span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">;</span></div><div class='line' id='LC220'>				<span class="nx">$backdrop</span><span class="p">.</span><span class="nx">off</span><span class="p">(</span><span class="s1">&#39;.modalmanager&#39;</span><span class="p">);</span></div><div class='line' id='LC221'>				<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span> <span class="o">=</span> <span class="kc">null</span><span class="p">;</span></div><div class='line' id='LC222'>				<span class="k">this</span><span class="p">.</span><span class="nx">isLoading</span> <span class="o">&amp;&amp;</span> <span class="k">this</span><span class="p">.</span><span class="nx">removeSpinner</span><span class="p">();</span></div><div class='line' id='LC223'>			<span class="p">}</span></div><div class='line' id='LC224'><br/></div><div class='line' id='LC225'>			<span class="k">return</span> <span class="nx">$backdrop</span></div><div class='line' id='LC226'>		<span class="p">},</span></div><div class='line' id='LC227'><br/></div><div class='line' id='LC228'>		<span class="nx">removeContainer</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC229'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$container</span><span class="p">.</span><span class="nx">remove</span><span class="p">();</span></div><div class='line' id='LC230'>			<span class="nx">modal</span><span class="p">.</span><span class="nx">$container</span> <span class="o">=</span> <span class="kc">null</span><span class="p">;</span></div><div class='line' id='LC231'>		<span class="p">},</span></div><div class='line' id='LC232'><br/></div><div class='line' id='LC233'>		<span class="nx">createContainer</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC234'>			<span class="kd">var</span> <span class="nx">$container</span><span class="p">;</span></div><div class='line' id='LC235'><br/></div><div class='line' id='LC236'>			<span class="nx">$container</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="s1">&#39;&lt;div class=&quot;modal-scrollable&quot;&gt;&#39;</span><span class="p">)</span></div><div class='line' id='LC237'>				<span class="p">.</span><span class="nx">css</span><span class="p">(</span><span class="s1">&#39;z-index&#39;</span><span class="p">,</span> <span class="nx">getzIndex</span><span class="p">(</span> <span class="s1">&#39;modal&#39;</span><span class="p">,</span></div><div class='line' id='LC238'>					<span class="nx">modal</span> <span class="o">?</span> <span class="k">this</span><span class="p">.</span><span class="nx">getIndexOfModal</span><span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="o">:</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span> <span class="p">))</span></div><div class='line' id='LC239'>				<span class="p">.</span><span class="nx">appendTo</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">$element</span><span class="p">);</span></div><div class='line' id='LC240'><br/></div><div class='line' id='LC241'>			<span class="k">if</span> <span class="p">(</span><span class="nx">modal</span> <span class="o">&amp;&amp;</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">options</span><span class="p">.</span><span class="nx">backdrop</span> <span class="o">!=</span> <span class="s1">&#39;static&#39;</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC242'>				<span class="nx">$container</span><span class="p">.</span><span class="nx">on</span><span class="p">(</span><span class="s1">&#39;click.modal&#39;</span><span class="p">,</span> <span class="nx">targetIsSelf</span><span class="p">(</span><span class="kd">function</span> <span class="p">(</span><span class="nx">e</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC243'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">hide</span><span class="p">();</span></div><div class='line' id='LC244'>				<span class="p">}));</span></div><div class='line' id='LC245'>			<span class="p">}</span> <span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC246'>				<span class="nx">$container</span><span class="p">.</span><span class="nx">on</span><span class="p">(</span><span class="s1">&#39;click.modal&#39;</span><span class="p">,</span> <span class="nx">targetIsSelf</span><span class="p">(</span><span class="kd">function</span> <span class="p">(</span><span class="nx">e</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC247'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">attention</span><span class="p">();</span></div><div class='line' id='LC248'>				<span class="p">}));</span></div><div class='line' id='LC249'>			<span class="p">}</span></div><div class='line' id='LC250'><br/></div><div class='line' id='LC251'>			<span class="k">return</span> <span class="nx">$container</span><span class="p">;</span></div><div class='line' id='LC252'><br/></div><div class='line' id='LC253'>		<span class="p">},</span></div><div class='line' id='LC254'><br/></div><div class='line' id='LC255'>		<span class="nx">backdrop</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">modal</span><span class="p">,</span> <span class="nx">callback</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC256'>			<span class="kd">var</span> <span class="nx">animate</span> <span class="o">=</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">hasClass</span><span class="p">(</span><span class="s1">&#39;fade&#39;</span><span class="p">)</span> <span class="o">?</span> <span class="s1">&#39;fade&#39;</span> <span class="o">:</span> <span class="s1">&#39;&#39;</span><span class="p">,</span></div><div class='line' id='LC257'>				<span class="nx">showBackdrop</span> <span class="o">=</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">options</span><span class="p">.</span><span class="nx">backdrop</span> <span class="o">&amp;&amp;</span></div><div class='line' id='LC258'>					<span class="k">this</span><span class="p">.</span><span class="nx">backdropCount</span> <span class="o">&lt;</span> <span class="k">this</span><span class="p">.</span><span class="nx">options</span><span class="p">.</span><span class="nx">backdropLimit</span><span class="p">;</span></div><div class='line' id='LC259'><br/></div><div class='line' id='LC260'>			<span class="k">if</span> <span class="p">(</span><span class="nx">modal</span><span class="p">.</span><span class="nx">isShown</span> <span class="o">&amp;&amp;</span> <span class="nx">showBackdrop</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC261'>				<span class="kd">var</span> <span class="nx">doAnimate</span> <span class="o">=</span> <span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span> <span class="o">&amp;&amp;</span> <span class="nx">animate</span> <span class="o">&amp;&amp;</span> <span class="o">!</span><span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">;</span></div><div class='line' id='LC262'><br/></div><div class='line' id='LC263'>				<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span> <span class="o">=</span> <span class="k">this</span><span class="p">.</span><span class="nx">createBackdrop</span><span class="p">(</span><span class="nx">animate</span><span class="p">);</span></div><div class='line' id='LC264'><br/></div><div class='line' id='LC265'>				<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">.</span><span class="nx">css</span><span class="p">(</span><span class="s1">&#39;z-index&#39;</span><span class="p">,</span> <span class="nx">getzIndex</span><span class="p">(</span> <span class="s1">&#39;backdrop&#39;</span><span class="p">,</span> <span class="k">this</span><span class="p">.</span><span class="nx">getIndexOfModal</span><span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">));</span></div><div class='line' id='LC266'><br/></div><div class='line' id='LC267'>				<span class="k">if</span> <span class="p">(</span><span class="nx">doAnimate</span><span class="p">)</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">[</span><span class="mi">0</span><span class="p">].</span><span class="nx">offsetWidth</span><span class="p">;</span> <span class="c1">// force reflow</span></div><div class='line' id='LC268'><br/></div><div class='line' id='LC269'>				<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">.</span><span class="nx">addClass</span><span class="p">(</span><span class="s1">&#39;in&#39;</span><span class="p">);</span></div><div class='line' id='LC270'><br/></div><div class='line' id='LC271'>				<span class="k">this</span><span class="p">.</span><span class="nx">backdropCount</span> <span class="o">+=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC272'><br/></div><div class='line' id='LC273'>				<span class="nx">doAnimate</span> <span class="o">?</span></div><div class='line' id='LC274'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">.</span><span class="nx">one</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span><span class="p">.</span><span class="nx">end</span><span class="p">,</span> <span class="nx">callback</span><span class="p">)</span> <span class="o">:</span></div><div class='line' id='LC275'>					<span class="nx">callback</span><span class="p">();</span></div><div class='line' id='LC276'><br/></div><div class='line' id='LC277'>			<span class="p">}</span> <span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="nx">modal</span><span class="p">.</span><span class="nx">isShown</span> <span class="o">&amp;&amp;</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC278'>				<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">.</span><span class="nx">removeClass</span><span class="p">(</span><span class="s1">&#39;in&#39;</span><span class="p">);</span></div><div class='line' id='LC279'><br/></div><div class='line' id='LC280'>				<span class="k">this</span><span class="p">.</span><span class="nx">backdropCount</span> <span class="o">-=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC281'><br/></div><div class='line' id='LC282'>				<span class="kd">var</span> <span class="nx">that</span> <span class="o">=</span> <span class="k">this</span><span class="p">;</span></div><div class='line' id='LC283'><br/></div><div class='line' id='LC284'>				<span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span> <span class="o">&amp;&amp;</span> <span class="nx">modal</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">hasClass</span><span class="p">(</span><span class="s1">&#39;fade&#39;</span><span class="p">)</span><span class="o">?</span></div><div class='line' id='LC285'>					<span class="nx">modal</span><span class="p">.</span><span class="nx">$backdrop</span><span class="p">.</span><span class="nx">one</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span><span class="p">.</span><span class="nx">end</span><span class="p">,</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span> <span class="nx">that</span><span class="p">.</span><span class="nx">removeBackdrop</span><span class="p">(</span><span class="nx">modal</span><span class="p">)</span> <span class="p">})</span> <span class="o">:</span></div><div class='line' id='LC286'>					<span class="nx">that</span><span class="p">.</span><span class="nx">removeBackdrop</span><span class="p">(</span><span class="nx">modal</span><span class="p">);</span></div><div class='line' id='LC287'><br/></div><div class='line' id='LC288'>			<span class="p">}</span> <span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="nx">callback</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC289'>				<span class="nx">callback</span><span class="p">();</span></div><div class='line' id='LC290'>			<span class="p">}</span></div><div class='line' id='LC291'>		<span class="p">},</span></div><div class='line' id='LC292'><br/></div><div class='line' id='LC293'>		<span class="nx">removeSpinner</span><span class="o">:</span> <span class="kd">function</span><span class="p">(){</span></div><div class='line' id='LC294'>			<span class="k">this</span><span class="p">.</span><span class="nx">$spinner</span> <span class="o">&amp;&amp;</span> <span class="k">this</span><span class="p">.</span><span class="nx">$spinner</span><span class="p">.</span><span class="nx">remove</span><span class="p">();</span></div><div class='line' id='LC295'>			<span class="k">this</span><span class="p">.</span><span class="nx">$spinner</span> <span class="o">=</span> <span class="kc">null</span><span class="p">;</span></div><div class='line' id='LC296'>			<span class="k">this</span><span class="p">.</span><span class="nx">isLoading</span> <span class="o">=</span> <span class="kc">false</span><span class="p">;</span></div><div class='line' id='LC297'>		<span class="p">},</span></div><div class='line' id='LC298'><br/></div><div class='line' id='LC299'>		<span class="nx">removeLoading</span><span class="o">:</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC300'>			<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span> <span class="o">&amp;&amp;</span> <span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">.</span><span class="nx">remove</span><span class="p">();</span></div><div class='line' id='LC301'>			<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span> <span class="o">=</span> <span class="kc">null</span><span class="p">;</span></div><div class='line' id='LC302'>			<span class="k">this</span><span class="p">.</span><span class="nx">removeSpinner</span><span class="p">();</span></div><div class='line' id='LC303'>		<span class="p">},</span></div><div class='line' id='LC304'><br/></div><div class='line' id='LC305'>		<span class="nx">loading</span><span class="o">:</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">callback</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC306'>			<span class="nx">callback</span> <span class="o">=</span> <span class="nx">callback</span> <span class="o">||</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span> <span class="p">};</span></div><div class='line' id='LC307'><br/></div><div class='line' id='LC308'>			<span class="k">this</span><span class="p">.</span><span class="nx">$element</span></div><div class='line' id='LC309'>				<span class="p">.</span><span class="nx">toggleClass</span><span class="p">(</span><span class="s1">&#39;modal-open&#39;</span><span class="p">,</span> <span class="o">!</span><span class="k">this</span><span class="p">.</span><span class="nx">isLoading</span> <span class="o">||</span> <span class="k">this</span><span class="p">.</span><span class="nx">hasOpenModal</span><span class="p">())</span></div><div class='line' id='LC310'>				<span class="p">.</span><span class="nx">toggleClass</span><span class="p">(</span><span class="s1">&#39;page-overflow&#39;</span><span class="p">,</span> <span class="nx">$</span><span class="p">(</span><span class="nb">window</span><span class="p">).</span><span class="nx">height</span><span class="p">()</span> <span class="o">&lt;</span> <span class="k">this</span><span class="p">.</span><span class="nx">$element</span><span class="p">.</span><span class="nx">height</span><span class="p">());</span></div><div class='line' id='LC311'><br/></div><div class='line' id='LC312'>			<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="k">this</span><span class="p">.</span><span class="nx">isLoading</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC313'><br/></div><div class='line' id='LC314'>				<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span> <span class="o">=</span> <span class="k">this</span><span class="p">.</span><span class="nx">createBackdrop</span><span class="p">(</span><span class="s1">&#39;fade&#39;</span><span class="p">);</span></div><div class='line' id='LC315'><br/></div><div class='line' id='LC316'>				<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">[</span><span class="mi">0</span><span class="p">].</span><span class="nx">offsetWidth</span><span class="p">;</span> <span class="c1">// force reflow</span></div><div class='line' id='LC317'><br/></div><div class='line' id='LC318'>				<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span></div><div class='line' id='LC319'>					<span class="p">.</span><span class="nx">css</span><span class="p">(</span><span class="s1">&#39;z-index&#39;</span><span class="p">,</span> <span class="nx">getzIndex</span><span class="p">(</span><span class="s1">&#39;backdrop&#39;</span><span class="p">,</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span><span class="p">))</span></div><div class='line' id='LC320'>					<span class="p">.</span><span class="nx">addClass</span><span class="p">(</span><span class="s1">&#39;in&#39;</span><span class="p">);</span></div><div class='line' id='LC321'><br/></div><div class='line' id='LC322'>				<span class="kd">var</span> <span class="nx">$spinner</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">options</span><span class="p">.</span><span class="nx">spinner</span><span class="p">)</span></div><div class='line' id='LC323'>					<span class="p">.</span><span class="nx">css</span><span class="p">(</span><span class="s1">&#39;z-index&#39;</span><span class="p">,</span> <span class="nx">getzIndex</span><span class="p">(</span><span class="s1">&#39;modal&#39;</span><span class="p">,</span> <span class="k">this</span><span class="p">.</span><span class="nx">stack</span><span class="p">.</span><span class="nx">length</span><span class="p">))</span></div><div class='line' id='LC324'>					<span class="p">.</span><span class="nx">appendTo</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">$element</span><span class="p">)</span></div><div class='line' id='LC325'>					<span class="p">.</span><span class="nx">addClass</span><span class="p">(</span><span class="s1">&#39;in&#39;</span><span class="p">);</span></div><div class='line' id='LC326'><br/></div><div class='line' id='LC327'>				<span class="k">this</span><span class="p">.</span><span class="nx">$spinner</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">createContainer</span><span class="p">())</span></div><div class='line' id='LC328'>					<span class="p">.</span><span class="nx">append</span><span class="p">(</span><span class="nx">$spinner</span><span class="p">)</span></div><div class='line' id='LC329'>					<span class="p">.</span><span class="nx">on</span><span class="p">(</span><span class="s1">&#39;click.modalmanager&#39;</span><span class="p">,</span> <span class="nx">$</span><span class="p">.</span><span class="nx">proxy</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">loading</span><span class="p">,</span> <span class="k">this</span><span class="p">));</span></div><div class='line' id='LC330'><br/></div><div class='line' id='LC331'>				<span class="k">this</span><span class="p">.</span><span class="nx">isLoading</span> <span class="o">=</span> <span class="kc">true</span><span class="p">;</span></div><div class='line' id='LC332'><br/></div><div class='line' id='LC333'>				<span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span> <span class="o">?</span></div><div class='line' id='LC334'>					<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">.</span><span class="nx">one</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span><span class="p">.</span><span class="nx">end</span><span class="p">,</span> <span class="nx">callback</span><span class="p">)</span> <span class="o">:</span></div><div class='line' id='LC335'>					<span class="nx">callback</span><span class="p">();</span></div><div class='line' id='LC336'><br/></div><div class='line' id='LC337'>			<span class="p">}</span> <span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">isLoading</span> <span class="o">&amp;&amp;</span> <span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC338'>				<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">.</span><span class="nx">removeClass</span><span class="p">(</span><span class="s1">&#39;in&#39;</span><span class="p">);</span></div><div class='line' id='LC339'><br/></div><div class='line' id='LC340'>				<span class="kd">var</span> <span class="nx">that</span> <span class="o">=</span> <span class="k">this</span><span class="p">;</span></div><div class='line' id='LC341'>				<span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span> <span class="o">?</span></div><div class='line' id='LC342'>					<span class="k">this</span><span class="p">.</span><span class="nx">$backdropHandle</span><span class="p">.</span><span class="nx">one</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">support</span><span class="p">.</span><span class="nx">transition</span><span class="p">.</span><span class="nx">end</span><span class="p">,</span> <span class="kd">function</span> <span class="p">()</span> <span class="p">{</span> <span class="nx">that</span><span class="p">.</span><span class="nx">removeLoading</span><span class="p">()</span> <span class="p">})</span> <span class="o">:</span></div><div class='line' id='LC343'>					<span class="nx">that</span><span class="p">.</span><span class="nx">removeLoading</span><span class="p">();</span></div><div class='line' id='LC344'><br/></div><div class='line' id='LC345'>			<span class="p">}</span> <span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="nx">callback</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC346'>				<span class="nx">callback</span><span class="p">(</span><span class="k">this</span><span class="p">.</span><span class="nx">isLoading</span><span class="p">);</span></div><div class='line' id='LC347'>			<span class="p">}</span></div><div class='line' id='LC348'>		<span class="p">}</span></div><div class='line' id='LC349'>	<span class="p">};</span></div><div class='line' id='LC350'><br/></div><div class='line' id='LC351'>	<span class="cm">/* PRIVATE METHODS</span></div><div class='line' id='LC352'><span class="cm">	* ======================= */</span></div><div class='line' id='LC353'><br/></div><div class='line' id='LC354'>	<span class="c1">// computes and caches the zindexes</span></div><div class='line' id='LC355'>	<span class="kd">var</span> <span class="nx">getzIndex</span> <span class="o">=</span> <span class="p">(</span><span class="kd">function</span> <span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC356'>		<span class="kd">var</span> <span class="nx">zIndexFactor</span><span class="p">,</span></div><div class='line' id='LC357'>			<span class="nx">baseIndex</span> <span class="o">=</span> <span class="p">{};</span></div><div class='line' id='LC358'><br/></div><div class='line' id='LC359'>		<span class="k">return</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">type</span><span class="p">,</span> <span class="nx">pos</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC360'><br/></div><div class='line' id='LC361'>			<span class="k">if</span> <span class="p">(</span><span class="k">typeof</span> <span class="nx">zIndexFactor</span> <span class="o">===</span> <span class="s1">&#39;undefined&#39;</span><span class="p">){</span></div><div class='line' id='LC362'>				<span class="kd">var</span> <span class="nx">$baseModal</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="s1">&#39;&lt;div class=&quot;modal hide&quot; /&gt;&#39;</span><span class="p">).</span><span class="nx">appendTo</span><span class="p">(</span><span class="s1">&#39;body&#39;</span><span class="p">),</span></div><div class='line' id='LC363'>					<span class="nx">$baseBackdrop</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="s1">&#39;&lt;div class=&quot;modal-backdrop hide&quot; /&gt;&#39;</span><span class="p">).</span><span class="nx">appendTo</span><span class="p">(</span><span class="s1">&#39;body&#39;</span><span class="p">);</span></div><div class='line' id='LC364'><br/></div><div class='line' id='LC365'>				<span class="nx">baseIndex</span><span class="p">[</span><span class="s1">&#39;modal&#39;</span><span class="p">]</span> <span class="o">=</span> <span class="o">+</span><span class="nx">$baseModal</span><span class="p">.</span><span class="nx">css</span><span class="p">(</span><span class="s1">&#39;z-index&#39;</span><span class="p">);</span></div><div class='line' id='LC366'>				<span class="nx">baseIndex</span><span class="p">[</span><span class="s1">&#39;backdrop&#39;</span><span class="p">]</span> <span class="o">=</span> <span class="o">+</span><span class="nx">$baseBackdrop</span><span class="p">.</span><span class="nx">css</span><span class="p">(</span><span class="s1">&#39;z-index&#39;</span><span class="p">);</span></div><div class='line' id='LC367'>				<span class="nx">zIndexFactor</span> <span class="o">=</span> <span class="nx">baseIndex</span><span class="p">[</span><span class="s1">&#39;modal&#39;</span><span class="p">]</span> <span class="o">-</span> <span class="nx">baseIndex</span><span class="p">[</span><span class="s1">&#39;backdrop&#39;</span><span class="p">];</span></div><div class='line' id='LC368'><br/></div><div class='line' id='LC369'>				<span class="nx">$baseModal</span><span class="p">.</span><span class="nx">remove</span><span class="p">();</span></div><div class='line' id='LC370'>				<span class="nx">$baseBackdrop</span><span class="p">.</span><span class="nx">remove</span><span class="p">();</span></div><div class='line' id='LC371'>				<span class="nx">$baseBackdrop</span> <span class="o">=</span> <span class="nx">$baseModal</span> <span class="o">=</span> <span class="kc">null</span><span class="p">;</span></div><div class='line' id='LC372'>			<span class="p">}</span></div><div class='line' id='LC373'><br/></div><div class='line' id='LC374'>			<span class="k">return</span> <span class="nx">baseIndex</span><span class="p">[</span><span class="nx">type</span><span class="p">]</span> <span class="o">+</span> <span class="p">(</span><span class="nx">zIndexFactor</span> <span class="o">*</span> <span class="nx">pos</span><span class="p">);</span></div><div class='line' id='LC375'><br/></div><div class='line' id='LC376'>		<span class="p">}</span></div><div class='line' id='LC377'>	<span class="p">}());</span></div><div class='line' id='LC378'><br/></div><div class='line' id='LC379'>	<span class="c1">// make sure the event target is the modal itself in order to prevent</span></div><div class='line' id='LC380'>	<span class="c1">// other components such as tabsfrom triggering the modal manager.</span></div><div class='line' id='LC381'>	<span class="c1">// if Boostsrap namespaced events, this would not be needed.</span></div><div class='line' id='LC382'>	<span class="kd">function</span> <span class="nx">targetIsSelf</span><span class="p">(</span><span class="nx">callback</span><span class="p">){</span></div><div class='line' id='LC383'>		<span class="k">return</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">e</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC384'>			<span class="k">if</span> <span class="p">(</span><span class="k">this</span> <span class="o">===</span> <span class="nx">e</span><span class="p">.</span><span class="nx">target</span><span class="p">){</span></div><div class='line' id='LC385'>				<span class="k">return</span> <span class="nx">callback</span><span class="p">.</span><span class="nx">apply</span><span class="p">(</span><span class="k">this</span><span class="p">,</span> <span class="nx">arguments</span><span class="p">);</span></div><div class='line' id='LC386'>			<span class="p">}</span></div><div class='line' id='LC387'>		<span class="p">}</span></div><div class='line' id='LC388'>	<span class="p">}</span></div><div class='line' id='LC389'><br/></div><div class='line' id='LC390'><br/></div><div class='line' id='LC391'>	<span class="cm">/* MODAL MANAGER PLUGIN DEFINITION</span></div><div class='line' id='LC392'><span class="cm">	* ======================= */</span></div><div class='line' id='LC393'><br/></div><div class='line' id='LC394'>	<span class="nx">$</span><span class="p">.</span><span class="nx">fn</span><span class="p">.</span><span class="nx">modalmanager</span> <span class="o">=</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">option</span><span class="p">,</span> <span class="nx">args</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC395'>		<span class="k">return</span> <span class="k">this</span><span class="p">.</span><span class="nx">each</span><span class="p">(</span><span class="kd">function</span> <span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC396'>			<span class="kd">var</span> <span class="nx">$this</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="k">this</span><span class="p">),</span></div><div class='line' id='LC397'>				<span class="nx">data</span> <span class="o">=</span> <span class="nx">$this</span><span class="p">.</span><span class="nx">data</span><span class="p">(</span><span class="s1">&#39;modalmanager&#39;</span><span class="p">);</span></div><div class='line' id='LC398'><br/></div><div class='line' id='LC399'>			<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="nx">data</span><span class="p">)</span> <span class="nx">$this</span><span class="p">.</span><span class="nx">data</span><span class="p">(</span><span class="s1">&#39;modalmanager&#39;</span><span class="p">,</span> <span class="p">(</span><span class="nx">data</span> <span class="o">=</span> <span class="k">new</span> <span class="nx">ModalManager</span><span class="p">(</span><span class="k">this</span><span class="p">,</span> <span class="nx">option</span><span class="p">)));</span></div><div class='line' id='LC400'>			<span class="k">if</span> <span class="p">(</span><span class="k">typeof</span> <span class="nx">option</span> <span class="o">===</span> <span class="s1">&#39;string&#39;</span><span class="p">)</span> <span class="nx">data</span><span class="p">[</span><span class="nx">option</span><span class="p">].</span><span class="nx">apply</span><span class="p">(</span><span class="nx">data</span><span class="p">,</span> <span class="p">[].</span><span class="nx">concat</span><span class="p">(</span><span class="nx">args</span><span class="p">))</span></div><div class='line' id='LC401'>		<span class="p">})</span></div><div class='line' id='LC402'>	<span class="p">};</span></div><div class='line' id='LC403'><br/></div><div class='line' id='LC404'>	<span class="nx">$</span><span class="p">.</span><span class="nx">fn</span><span class="p">.</span><span class="nx">modalmanager</span><span class="p">.</span><span class="nx">defaults</span> <span class="o">=</span> <span class="p">{</span></div><div class='line' id='LC405'>		<span class="nx">backdropLimit</span><span class="o">:</span> <span class="mi">999</span><span class="p">,</span></div><div class='line' id='LC406'>		<span class="nx">resize</span><span class="o">:</span> <span class="kc">true</span><span class="p">,</span></div><div class='line' id='LC407'>		<span class="nx">spinner</span><span class="o">:</span> <span class="s1">&#39;&lt;div class=&quot;loading-spinner fade&quot; style=&quot;width: 200px; margin-left: -100px;&quot;&gt;&lt;div class=&quot;progress progress-striped active&quot;&gt;&lt;div class=&quot;bar&quot; style=&quot;width: 100%;&quot;&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&#39;</span></div><div class='line' id='LC408'>	<span class="p">};</span></div><div class='line' id='LC409'><br/></div><div class='line' id='LC410'>	<span class="nx">$</span><span class="p">.</span><span class="nx">fn</span><span class="p">.</span><span class="nx">modalmanager</span><span class="p">.</span><span class="nx">Constructor</span> <span class="o">=</span> <span class="nx">ModalManager</span></div><div class='line' id='LC411'><br/></div><div class='line' id='LC412'><span class="p">}(</span><span class="nx">jQuery</span><span class="p">);</span></div></pre></div>
          </td>
        </tr>
      </table>
  </div>

          </div>
        </div>

        <a href="#jump-to-line" rel="facebox" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
        <div id="jump-to-line" style="display:none">
          <h2>Jump to Line</h2>
          <form accept-charset="UTF-8" class="js-jump-to-line-form">
            <input class="textfield js-jump-to-line-field" type="text">
            <div class="full-button">
              <button type="submit" class="button">Go</button>
            </div>
          </form>
        </div>

      </div>
    </div>
</div>

<div id="js-frame-loading-template" class="frame frame-loading large-loading-area" style="display:none;">
  <img class="js-frame-loading-spinner" src="https://a248.e.akamai.net/assets.github.com/images/spinners/octocat-spinner-128.gif?1347543527" height="64" width="64">
</div>


        </div>
      </div>
      <div class="context-overlay"></div>
    </div>

      <div id="footer-push"></div><!-- hack for sticky footer -->
    </div><!-- end of wrapper - hack for sticky footer -->

      <!-- footer -->
      <div id="footer">
  <div class="container clearfix">

      <dl class="footer_nav">
        <dt>GitHub</dt>
        <dd><a href="https://github.com/about">About us</a></dd>
        <dd><a href="https://github.com/blog">Blog</a></dd>
        <dd><a href="https://github.com/contact">Contact &amp; support</a></dd>
        <dd><a href="http://enterprise.github.com/">GitHub Enterprise</a></dd>
        <dd><a href="http://status.github.com/">Site status</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Applications</dt>
        <dd><a href="http://mac.github.com/">GitHub for Mac</a></dd>
        <dd><a href="http://windows.github.com/">GitHub for Windows</a></dd>
        <dd><a href="http://eclipse.github.com/">GitHub for Eclipse</a></dd>
        <dd><a href="http://mobile.github.com/">GitHub mobile apps</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Services</dt>
        <dd><a href="http://get.gaug.es/">Gauges: Web analytics</a></dd>
        <dd><a href="http://speakerdeck.com">Speaker Deck: Presentations</a></dd>
        <dd><a href="https://gist.github.com">Gist: Code snippets</a></dd>
        <dd><a href="http://jobs.github.com/">Job board</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Documentation</dt>
        <dd><a href="http://help.github.com/">GitHub Help</a></dd>
        <dd><a href="http://developer.github.com/">Developer API</a></dd>
        <dd><a href="http://github.github.com/github-flavored-markdown/">GitHub Flavored Markdown</a></dd>
        <dd><a href="http://pages.github.com/">GitHub Pages</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>More</dt>
        <dd><a href="http://training.github.com/">Training</a></dd>
        <dd><a href="https://github.com/edu">Students &amp; teachers</a></dd>
        <dd><a href="http://shop.github.com">The Shop</a></dd>
        <dd><a href="/plans">Plans &amp; pricing</a></dd>
        <dd><a href="http://octodex.github.com/">The Octodex</a></dd>
      </dl>

      <hr class="footer-divider">


    <p class="right">&copy; 2013 <span title="0.03930s from fe16.rs.github.com">GitHub</span>, Inc. All rights reserved.</p>
    <a class="left" href="https://github.com/">
      <span class="mega-icon mega-icon-invertocat"></span>
    </a>
    <ul id="legal">
        <li><a href="https://github.com/site/terms">Terms of Service</a></li>
        <li><a href="https://github.com/site/privacy">Privacy</a></li>
        <li><a href="https://github.com/security">Security</a></li>
    </ul>

  </div><!-- /.container -->

</div><!-- /.#footer -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
          <div class="suggester-container">
              <div class="suggester fullscreen-suggester js-navigation-container" id="fullscreen_suggester"
                 data-url="/jschr/bootstrap-modal/suggestions/commit">
              </div>
          </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped leftwards" title="Exit Zen Mode">
      <span class="mega-icon mega-icon-normalscreen"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped leftwards"
      title="Switch themes">
      <span class="mini-icon mini-icon-brightness"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="mini-icon mini-icon-exclamation"></span>
      Something went wrong with that request. Please try again.
      <a href="#" class="mini-icon mini-icon-remove-close ajax-error-dismiss"></a>
    </div>

    
    
    <span id='server_response_time' data-time='0.03969' data-host='fe16'></span>
    
  </body>
</html>

