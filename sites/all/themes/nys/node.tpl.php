<?php
// $Id: node.tpl.php,v 1.4 2008/09/15 08:11:49 johnalbin Exp $

/**
 * @file node.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *   theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *   format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *   from theme_links().
 * - $name: Themed username of node author output from theme_user().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 */

?>


<?php
//// FRONT PAGE TABBED BLOCK NODES : HAPPENING NOW... BLOCK

if ($is_front && $teaser):?>

  <?php
   $node_user = user_load($node->uid);
  //dsm($node_user);
  //dsm($senator);
  if ($senator->field_profile_picture['0']['filepath']) {
    $picture = theme('imagecache', 'senator_teaser_front', $senator->field_profile_picture['0']['filepath'], $alt, $title, $attributes);
  };
  ?>

  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>">
    <div class="node-inner">

      <div class="meta">

        <?php if ($senator):?>
          <div class="senator_picture">
            <?php print l($picture, 'node/'.$node->nid, array('html'=>'TRUE')); ?>
          </div>
        <?php endif;?>

        <div class="right <?php if($picture){print 'with-image';}?>">

          <h4 class="title">
            <a href="<?php print $node_url; ?>" title="<?php print $node->title ?>"><?php print $node->title; ?></a>
          </h4>

          <?php if ($senator->title): ?>
            <div class="senator_title"><?php print $senator->title; ?></div>
          <?php endif;?>

          <div class="date"><?php print format_date($node->created, 'custom', 'M jS, Y'); ?></div>

        </div>

        <div class="clearfix"></div>

      </div>

      <div class="content">
        <?php print $node->teaser; ?>
      </div>

        <?php print l('Read more...', 'node/'.$node->nid, array('attributes' => array('class' => 'read_more')))?>

    </div>
  </div> <!-- /node-inner, /node -->

<?php
// HYBRID FULL/TEASER VIEW FOR SENATOR'S HOMEPAGE BLOG
elseif (($teaser && $node->type == 'blog') && ($senator->nid == arg(1) && arg(0) == 'node')): ?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>">
  <div class="node-inner">

    <?php if ($unpublished): ?>
      <div class="unpublished"><?php print t('Unpublished'); ?></div>
    <?php endif; ?>

    <?php print l('RSS Feed', 'senator/'.str_replace(' ','_',strtolower($senator->title)).'/blog/feed', array('attributes' => array('class'=>'rss_icon'))); ?>

      <h2 class="title">
        <?php print l($node->title, 'node/'.$node->nid); ?>
      </h2>

    <?php if ($submitted or $terms): ?>
      <div class="meta">
        <?php if ($submitted && $node->type == 'blog'): ?>
          <div class="submitted">
          <?php print $submitted; ?>
          </div>
        <?php endif; ?>
        <div class="terms">
          <?php print $terms; ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($node->type != 'page'):?>
      <div class="share_links">
        <div class="inner">
          <h3>Share This:</h3>
          <?php print $service_links ?>
        </div>
      </div>
    <?php endif; ?>

    <div class="content">

      <?php if ($node->field_feature_image['0']['filepath']):?>
        <div class="featured_image">
          <?php
          print theme('imagecache', 'full_node_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']);
          ?>
        </div>
      <?php endif; ?>

      <?php if ($senator && arg(0) != 'blogs' && $node->type == 'blog'):?>
        <?php if ($teaser == TRUE) {
          print $node->teaser;
          print l('Read more...', 'node/'.$node->nid);
        } else {
          print $node->body;
        }?>
      <?php else:?>
        <?php print $content; ?>
      <?php endif; ?>
    </div>

    <?php if ($links): ?>
      <?php print $links; ?>
    <?php endif; ?>

  </div>
</div> <!-- /node-inner, /node -->

<?php print l('RSS Feed', 'senator/'.str_replace(' ','_',strtolower($senator->title)).'/blog/feed', array('attributes' => array('class'=>'rss_icon'))); ?>

<?php if (!$user->uid) {
  print '<div class="login_register">'.l('Login', 'user/login').' or '. l('Register','user/register') .' to post comments</div>';
}?>

<?php
// BLOG, LEGISLATION AND IN THE NEWS TEASERS
elseif (($teaser && ($node->type == 'blog' || $node->type == 'press_release'  || $node->type == 'in_the_news' || $node->type == 'report' || $node->type == 'legislation' ))): ?>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
    <div class="node-inner">

      <h3 class="title">
        <?php print l($node->title, 'node/'.$node->nid); ?>
      </h3>

      <?php if ($unpublished): ?>
        <div class="unpublished"><?php print t('Unpublished'); ?></div>
      <?php endif; ?>

      <?php if ($submitted or $terms): ?>
        <div class="meta">
          <?php if ($submitted): ?>
            <div class="submitted">
              <?php print $submitted; ?>
            </div>
          <?php endif; ?>
          <div class="terms">
            <?php print $terms; ?>
          </div>
        </div>
      <?php endif; ?>

      <div class="content">

        <?php if ($node->field_feature_image['0']['filepath']):?>
        <div class="featured_image">
            <?php
          print theme('imagecache', 'teaser_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']);
          ?>
        </div>
        <?php endif; ?>

        <?php print $content; ?>
        <?php print l('Read more...', 'node/' . $node->nid); ?>
      </div>

      <?php if ($links): ?>
        <?php print $links; ?>
      <?php endif; ?>

  </div>
</div> <!-- /node-inner, /node -->

<?php elseif ($teaser):
// REGULAR TEASERS ?>
  
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
    <div class="node-inner">
      
      <h3 class="title">
        <?php print l($node->title, 'node/'.$node->nid); ?>
      </h3>

      <?php if ($unpublished): ?>
        <div class="unpublished"><?php print t('Unpublished'); ?></div>
      <?php endif; ?>

      <?php if ($submitted or $terms): ?>
        <div class="meta">
          <?php if ($submitted && in_array($node->type, array('blog', 'report', 'press_release', 'in_the_news'))): ?>
            <div class="submitted">
            <?php print $submitted; ?>
            </div>
          <?php endif; ?>
          <div class="terms">
            <?php print $terms; ?>
          </div>
        </div>
      <?php endif; ?>

      <div class="content">

        <?php if ($node->field_feature_image['0']['filepath']):?>
          <div class="featured_image">
            <?php
            print theme('imagecache', 'teaser_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']);
            ?>
          </div>
        <?php endif; ?>
          <?php print $content; ?>
      </div>

      <?php if ($links): ?>
        <?php print $links; ?>
      <?php endif; ?>

    </div>
  </div> <!-- /node-inner, /node -->

<?php elseif (($node->type == 'outline') || ($node->type == 'legislation_outline') || ($node->type == 'page_legislation')):
// BOOK NODE
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <div class="node-inner">
    <?php if ($unpublished): ?>
      <div class="unpublished"><?php print t('Unpublished'); ?></div>
    <?php endif; ?>

    <?php if ($submitted or $terms): ?>
      <div class="meta">
        <div class="terms">
          <?php print $terms; ?>
        </div>
      </div>
    <?php endif; ?>

    <div class="content">

      <?php if ($node->field_feature_image['0']['filepath'] && $node->type != 'video' && $node->type != 'page'):?>
        <div class="featured_image">
          <?php
          print theme('imagecache', 'full_node_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']);
          ?>
        </div>
      <?php endif; ?>
        <?php print $content; ?>
    </div>

    <?php if ($links): ?>
      <?php print $links; ?>
    <?php endif; ?>
    
    <?php if (!$user->uid && $node->comment > 0) {
      print '<div class="legislation_comment_add">&mdash;'.l('Login', 'user/login', array('query' => 'destination=comment/reply/'.$node->nid.urlencode('%23comment-form'))).' or '. l('Register','user/register', array('query' => 'destination=comment/reply/'.$node->nid.urlencode('%23comment-form'))) .' to comment on this legislation&mdash;</div>';
    }
    else if ($node->comment > 0) {
      print '<div class="legislation_comment_add">&mdash;'.l('Post a comment about this legislation', 'comment/reply/'. $node->nid, array('fragment'=>'comment-form')).'&mdash;</div>';
    }?>


  </div>
</div> <!-- /node-inner, /node -->



<?php else:
// FULL NODE
?>
<?php drupal_add_js(path_to_theme() . '/js/jquery.csv2table-0.02-b-2.8.js', 'theme'); ?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <div class="node-inner">

    <?php if ($unpublished): ?>
      <div class="unpublished"><?php print t('Unpublished'); ?></div>
    <?php endif; ?>

    <?php if ($node->type == 'blog'):?>
      <?php if ($node->field_senator[0]['nid'] != '') { ?>
        <?php print l('RSS Feed', 'senator/'.str_replace(' ','_',strtolower($senator->title)).'/blog/feed', array('attributes' => array('class'=>'rss_icon'))); ?>
      <?php } else { ?>
        <?php print l('Rss Feed', 'blog/feed', array('attributes' => array('class'=>'rss_icon'))); ?>
      <?php } ?>
    <?php endif; ?>

    <?php if ($submitted or $terms): ?>
      <div class="meta">
        <?php if ($submitted && in_array($node->type, array('blog', 'report', 'in_the_news', 'press_release'))): ?>
          <div class="submitted">
          <?php print $submitted; ?>
          </div>
        <?php endif; ?>
        <div class="terms">
          <?php print $terms; ?>
        </div>
      </div>
    <?php endif; ?>

    <div class="share_links">
      <div class="inner">
        <h3>Share This:</h3>
        <?php print $service_links ?>
      </div>
    </div>
  
    <div class="content">

      <?php if ($node->field_feature_image['0']['filepath'] && $node->type != 'video' && $node->type != 'page'):?>
        <div class="featured_image">
          <?php
          print theme('imagecache', 'full_node_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']);
          ?>
        </div>
      <?php endif; ?>
        <?php print $content; ?>
    </div>

    <?php if ($links): ?>
      <?php print $links; ?>
    <?php endif; ?>

  </div>
</div> <!-- /node-inner, /node -->

<?php endif; ?>
