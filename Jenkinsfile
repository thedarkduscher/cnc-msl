node {
    stage('scm'){
        checkout scm
    }

    stage ('reference') {
        echo "We are currently working on branch: ${env.BRANCH_NAME}"

        if(env.BRANCH_NAME == 'master') {
            sh 'pip3 install pystache'
            sh 'git branch -f gh-pages'
            sh 'git checkout gh-pages'
            sh 'doxygen'
            sh 'doxygen_renderer docs/xml docs/public'
            sh 'git add docs/public'
            sh 'git commit -m "Build reference"'
            sh 'git filter-branch -f --prune-empty --subdirectory-filter docs/public'
            sh 'git push -f origin gh-pages'
        }
    }
}
