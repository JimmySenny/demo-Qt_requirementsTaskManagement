-- t_vers_info  版本信息表
CREATE TABLE `t_vers_info`
(
    `id` varchar(32) NOT NULL COMMENT '主键ID',
    `ver_no` varchar(50) NOT NULL COMMENT '版本号',
    `sys_id` char(4) NOT NULL COMMENT '归属系统ID',
    `ver_name` varchar(128) NOT NULL COMMENT '版本包文件名称',
    `src_name` varchar(128) DEFAULT NULL COMMENT '原始包文件名称',
    `doc_name` varchar(128) DEFAULT NULL COMMENT '附带文档名称',
    `dtalst_id` varchar(128) DEFAULT NULL COMMENT '入口控制DTA列表ID',
    `alalst_id` varchar(128) DEFAULT NULL COMMENT '涉及ALA列表ID',
    `ver_type` char(1) NOT NULL COMMENT '版本类型',
    `ref_type` char(1) NOT NULL COMMENT '生效类型',
    `ver_path` varchar(128) NOT NULL COMMENT '版本所在路径',
    `chk_user` varchar(64) NOT NULL COMMENT '审核用户ID',
    `dep_flag` char(1) NOT NULL COMMENT '部署标志',
    `ref_flag` char(1) NOT NULL COMMENT '生效标志',
    `redo_flag` char(1) NOT NULL COMMENT '回退标志',
    `com_flag` char(1) NOT NULL COMMENT '是否涉及公共',
    `stat` char(1) NOT NULL COMMENT '版本状态',
    `create_by` varchar(64) DEFAULT NULL COMMENT '创建者',
    `create_date` varchar(20) DEFAULT NULL COMMENT '创建时间',
    `update_by` varchar(64) DEFAULT NULL COMMENT '更新者',
    `update_date` varchar(20) DEFAULT NULL COMMENT '更新时间',
    `del_flag` char(1) DEFAULT NULL COMMENT '删除标志',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '备用字段1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '备用字段2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '备用字段3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '备用字段4',
    `remarks` varchar(255) DEFAULT NULL COMMENT '备注信息'
) COMMENT='版本信息表';

ALTER TABLE `t_vers_info` ADD PRIMARY KEY (id);

ALTER TABLE `t_vers_info` ADD UNIQUE (ver_no);


-- tb_rmt_user  用户信息表
CREATE TABLE `tb_rmt_user`
(
    `user_id` varchar(16) NOT NULL COMMENT '用户ID',
    `user_name` varchar(60) NOT NULL COMMENT '用户名称',
    `user_pwd` varchar(16) NOT NULL COMMENT '用户密码',
    `user_level` char(2) DEFAULT NULL COMMENT '用户级别',
    `user_depm` char(2) DEFAULT NULL COMMENT '用户归口部门',
    `user_team` char(2) DEFAULT NULL COMMENT '用户归口团队',
    `user_status` char(2) NOT NULL COMMENT '用户状态',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '备用字段1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '备用字段2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '备用字段3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '备用字段4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC字段'
) COMMENT='用户信息表';

ALTER TABLE `tb_rmt_user` ADD PRIMARY KEY (user_id);



-- tb_rmt_enum  枚举信息表
CREATE TABLE `tb_rmt_enum`
(
    `enum_name` char(50) DEFAULT NULL COMMENT '枚举名称',
    `enum_status` char(2) DEFAULT NULL COMMENT '枚举记录状态',
    `enum_key` char(50) DEFAULT NULL COMMENT '枚举键值',
    `enum_value` char(100) DEFAULT NULL COMMENT '枚举值',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '备用字段1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '备用字段2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '备用字段3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '备用字段4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC字段'
) COMMENT='枚举信息表';




-- tb_rmt_requirements  需求基本信息表
CREATE TABLE `tb_rmt_requirements`
(
    `uuid` char(32) NOT NULL COMMENT 'uuid',
    `req_no` varchar(32) NOT NULL COMMENT '需求编号',
    `req_type` char(2) NOT NULL COMMENT '需求类型',
    `sys_attr` char(2) NOT NULL COMMENT '需求属性',
    `req_name` varchar(128) NOT NULL COMMENT '需求简述',
    `req_desc` varchar(1024) DEFAULT NULL COMMENT '需求描述',
    `req_dpm` varchar(20) DEFAULT NULL COMMENT '需求提出部门',
    `req_busiop` varchar(16) DEFAULT NULL COMMENT '需求经办人',
    `req_inputdt` char(19) DEFAULT NULL COMMENT '需求提交时间',
    `req_expectdt` char(19) DEFAULT NULL COMMENT '期望交付时间',
    `req_busicheck` varchar(16) DEFAULT NULL COMMENT '需求审核人',
    `req_checkdt` char(19) DEFAULT NULL COMMENT '需求审核时间',
    `req_level` char(1) DEFAULT NULL COMMENT '需求优先级',
    `req_disop` varchar(16) DEFAULT NULL COMMENT '需求分配人',
    `req_disdt` char(19) DEFAULT NULL COMMENT '需求分配时间',
    `req_team` varchar(20) DEFAULT NULL COMMENT '需求牵头团队',
    `req_teamlader` varchar(16) DEFAULT NULL COMMENT '需求牵头团队负责人',
    `req_system` varchar(10) DEFAULT NULL COMMENT '需求牵头系统',
    `req_tecoperator` varchar(16) DEFAULT NULL COMMENT '需求牵头经办人',
    `req_relation` varchar(100) DEFAULT NULL COMMENT '需求关联系统',
    `req_stat` char(2) DEFAULT NULL COMMENT '需求当前阶段',
    `req_plandt` char(19) DEFAULT NULL COMMENT '需求计划完成时间',
    `req_donedt` char(19) DEFAULT NULL COMMENT '需求计划实际时间',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '备用字段1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '备用字段2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '备用字段3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '备用字段4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC字段'
) COMMENT='需求基本信息表';

ALTER TABLE `tb_rmt_requirements` ADD PRIMARY KEY (uuid);

ALTER TABLE `tb_rmt_requirements` ADD UNIQUE (req_no);


-- tb_rmt_task  任务基本信息表
CREATE TABLE `tb_rmt_task`
(
    `uuid` char(32) NOT NULL COMMENT 'uuid',
    `req_no` varchar(32) NOT NULL COMMENT '关联需求编号',
    `task_no` varchar(32) NOT NULL COMMENT '任务编号',
    `task_type` char(2) DEFAULT NULL COMMENT '任务类型',
    `task_attr` char(2) DEFAULT NULL COMMENT '任务属性',
    `task_name` varchar(128) DEFAULT NULL COMMENT '任务简述',
    `task_desc` varchar(1024) DEFAULT NULL COMMENT '任务描述',
    `task_inputdt` char(19) DEFAULT NULL COMMENT '任务分配时间',
    `task_expectdt` char(19) DEFAULT NULL COMMENT '任务期望交付时间',
    `task_level` char(1) DEFAULT NULL COMMENT '任务优先级',
    `task_team` varchar(20) DEFAULT NULL COMMENT '任务归属团队',
    `task_teamlader` varchar(16) DEFAULT NULL COMMENT '任务归属团队负责人',
    `task_system` varchar(10) DEFAULT NULL COMMENT '任务归属系统',
    `task_tecop` varchar(16) DEFAULT NULL COMMENT '任务技术经办人',
    `task_stat` char(2) DEFAULT NULL COMMENT '任务当前阶段',
    `task_plandt` char(19) DEFAULT NULL COMMENT '任务计划完成时间',
    `task_donedt` char(19) DEFAULT NULL COMMENT '任务实际完成时间',
    `task_partyop` varchar(16) DEFAULT NULL COMMENT '任务合作厂商负责人',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '备用字段1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '备用字段2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '备用字段3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '备用字段4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC字段'
) COMMENT='任务基本信息表';

ALTER TABLE `tb_rmt_task` ADD PRIMARY KEY (uuid);

ALTER TABLE `tb_rmt_task` ADD UNIQUE (task_no);

ALTER TABLE `tb_rmt_task` ADD INDEX index_name(req_no);

